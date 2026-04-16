package com.zeroone.star.material.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.material.entity.MaterialDO;
import com.zeroone.star.material.entity.MaterialRecordDO;
import com.zeroone.star.material.mapper.MaterialRecordMapper;
import com.zeroone.star.material.service.IMaterialRecordService;
import com.zeroone.star.material.service.IMaterialService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.material.MaterialRecordDTO;
import com.zeroone.star.project.query.j9.material.MaterialRecordQuery;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

/**
 * <p>
 * 物料出入库记录 服务实现类
 * </p>
 *
 * @author fantast
 * @since 2026-03-16
 */
@Service
public class MaterialRecordServiceImpl extends ServiceImpl<MaterialRecordMapper, MaterialRecordDO> implements IMaterialRecordService {

    @Resource
    private IMaterialService materialService;

    @Resource
    private UserHolder userHolder;

    @Override
    @Transactional(rollbackFor = Exception.class)
    public List<Long> saveInStorage(List<Long> ids, int amount) {
        List<Long> resultIds = new ArrayList<>();
        LocalDateTime now = LocalDateTime.now();
        Long currentUserId = null;
        try {
            UserDTO currentUser = userHolder.getCurrentUser();
            currentUserId = Long.valueOf(currentUser.getId());
        } catch (Exception e) {
        }

        for (Long materialId : ids) {
            MaterialDO material = materialService.getById(materialId);
            if (material != null) {
                MaterialRecordDO record = new MaterialRecordDO();
                record.setMaterialId(materialId);
                record.setAmount(amount);
                record.setChangeType(1);
                record.setAddTime(now);
                record.setEditTime(now);
                record.setDeleted(false);
                record.setOrgId(material.getOrgId());
                record.setSchoolId(material.getSchoolId());
                if (currentUserId != null) {
                    record.setCreator(currentUserId);
                    record.setEditor(currentUserId);
                }
                baseMapper.insert(record);
                resultIds.add(record.getId());

                LambdaUpdateWrapper<MaterialDO> updateWrapper = new LambdaUpdateWrapper<>();
                updateWrapper.eq(MaterialDO::getId, materialId)
                        .setSql("storage = storage + " + amount);
                materialService.update(updateWrapper);
            }
        }
        return resultIds;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public List<Long> saveOutStorage(List<Long> ids, int amount) {
        List<Long> resultIds = new ArrayList<>();
        LocalDateTime now = LocalDateTime.now();
        Long currentUserId = null;
        try {
            UserDTO currentUser = userHolder.getCurrentUser();
            currentUserId = Long.valueOf(currentUser.getId());
        } catch (Exception e) {
        }

        for (Long materialId : ids) {
            MaterialDO material = materialService.getById(materialId);
            if (material != null && material.getStorage() >= amount) {
                MaterialRecordDO record = new MaterialRecordDO();
                record.setMaterialId(materialId);
                record.setAmount(-amount);
                record.setChangeType(2);
                record.setAddTime(now);
                record.setEditTime(now);
                record.setDeleted(false);
                record.setOrgId(material.getOrgId());
                record.setSchoolId(material.getSchoolId());
                if (currentUserId != null) {
                    record.setCreator(currentUserId);
                    record.setEditor(currentUserId);
                }
                baseMapper.insert(record);
                resultIds.add(record.getId());

                LambdaUpdateWrapper<MaterialDO> updateWrapper = new LambdaUpdateWrapper<>();
                updateWrapper.eq(MaterialDO::getId, materialId)
                        .setSql("storage = storage - " + amount);
                materialService.update(updateWrapper);
            }
        }
        return resultIds;
    }

    @Override
    public PageDTO<MaterialRecordDTO> listPage(MaterialRecordQuery query) {
        Page<MaterialRecordDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        baseMapper.selectMaterialRecordList(page, query);
        PageDTO<MaterialRecordDTO> result = new PageDTO<>();
        result.setPageIndex(page.getCurrent());
        result.setPageSize(page.getSize());
        result.setTotal(page.getTotal());
        result.setPages(page.getPages());
        result.setRows(page.getRecords());
        return result;
    }

}
