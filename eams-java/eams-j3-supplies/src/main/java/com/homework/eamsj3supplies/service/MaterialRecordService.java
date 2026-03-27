package com.homework.eamsj3supplies.service;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.baomidou.mybatisplus.extension.conditions.update.LambdaUpdateChainWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.homework.eamsj3supplies.constant.MaterialChangeTypeEnum;
import com.homework.eamsj3supplies.mapper.MaterialMapper;
import com.homework.eamsj3supplies.mapper.MaterialRecordMapper;
import com.homework.eamsj3supplies.mapstruct.MaterialStructMapper;
import com.zeroone.star.project.DO.Material;
import com.zeroone.star.project.DO.MaterialRecord;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.supplies.MaterialStockChangedDTO;
import com.zeroone.star.project.dto.j3.supplies.MaterialStockChangeDTO;
import com.zeroone.star.project.query.j3.supplies.MaterialRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.supplies.MaterialRecordVO;
import com.zeroone.star.project.vo.j3.supplies.MaterialStockVO;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.validation.annotation.Validated;

import javax.annotation.Resource;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Date;
import java.util.concurrent.ThreadLocalRandom;

@Service
public class MaterialRecordService {
    @Resource
    private MaterialMapper materialMapper;
    @Resource
    private MaterialRecordMapper materialRecordMapper;
    @Resource
    private MaterialStructMapper materialStructMapper;

    @Transactional(rollbackFor = Exception.class)
    public JsonVO<MaterialStockVO> changeMaterialAmount(MaterialStockChangeDTO materialStockChangeDTO) {
        MaterialChangeTypeEnum changeTypeEnum = MaterialChangeTypeEnum.fromCode(materialStockChangeDTO.getChangeType());
        if (changeTypeEnum == null) {
            return JsonVO.fail("变动类型不合法");
        }

        int delta = changeTypeEnum.toDelta(materialStockChangeDTO.getAmount());
        LambdaUpdateChainWrapper<Material> updateChain = new LambdaUpdateChainWrapper<>(materialMapper);
        // 计算库存增减量：入库为正，出库为负
        updateChain.eq(Material::getId, materialStockChangeDTO.getMaterialId())
                .eq(Material::getDeleted, 0)
                .setSql("storage = storage + " + delta)
                .set(Material::getEditTime, new Date());
        if (delta < 0) {
            // 条件更新库存：避免库存扣成负数
            updateChain.ge(Material::getStorage, -delta);
        }
        int affected = updateChain.update() ? 1 : 0;
        if (affected <= 0) {
            return JsonVO.fail("库存不足或物料不存在");
        }

        Material material = materialMapper.selectById(materialStockChangeDTO.getMaterialId());
        if (material == null) {
            return JsonVO.fail("物料不存在");
        }

        MaterialRecord record = new MaterialRecord();
        record.setId(System.currentTimeMillis() + ThreadLocalRandom.current().nextInt(1000));
        record.setMaterialId(materialStockChangeDTO.getMaterialId());
        record.setAmount(delta);
        record.setReason(materialStockChangeDTO.getReason());
        record.setChangeType(changeTypeEnum.getCode());
        record.setDeleted(0);
        Date now = new Date();
        record.setAddTime(now);
        record.setEditTime(now);
        materialRecordMapper.insert(record);

        MaterialStockChangedDTO changedDTO = new MaterialStockChangedDTO();
        changedDTO.setName(material.getName());
        changedDTO.setStorage(material.getStorage());
        return JsonVO.success(materialStructMapper.toMaterialStockVO(changedDTO));
    }

    public JsonVO<PageDTO<MaterialRecordVO>> queryMaterialRecordPage(MaterialRecordQuery query) {
        if (query == null){
            return JsonVO.fail("query为空");
        }
        Page<MaterialRecord> page = new Page<>(query.getPageIndex(), query.getPageSize());
        IPage<MaterialRecord> pageData = materialRecordMapper.selectPage(
                page,
                Wrappers.<MaterialRecord>lambdaQuery()
                        .eq(MaterialRecord::getDeleted, 0)
                        .eq(query.getMaterialId() != null, MaterialRecord::getMaterialId, query.getMaterialId())
                        .eq(query.getStudentId() != null, MaterialRecord::getStudentId, query.getStudentId())
                        .eq(query.getApplyStaffId() != null, MaterialRecord::getStaffId, query.getApplyStaffId())
                        .eq(query.getChangeType() != null, MaterialRecord::getChangeType, query.getChangeType())
                        .ge(query.getBeginDate() != null && !query.getBeginDate().isEmpty(),
                                MaterialRecord::getAddTime, toDateTime(query.getBeginDate(), false))
                        .le(query.getEndDate() != null && !query.getEndDate().isEmpty(),
                                MaterialRecord::getAddTime, toDateTime(query.getEndDate(), true))
                        .orderByDesc(MaterialRecord::getAddTime)
        );

        PageDTO<MaterialRecordVO> result = new PageDTO<>();
        result.setPageIndex(pageData.getCurrent());
        result.setPageSize(pageData.getSize());
        result.setTotal(pageData.getTotal());
        result.setPages(pageData.getPages());
        result.setRows(materialStructMapper.toMaterialRecordVOList(pageData.getRecords()));
        return JsonVO.success(result);
    }

    private LocalDateTime toDateTime(String date, boolean endOfDay) {
        LocalDate parsed = LocalDate.parse(date, DateTimeFormatter.ISO_LOCAL_DATE);
        return endOfDay ? parsed.atTime(23, 59, 59) : parsed.atStartOfDay();
    }
}
