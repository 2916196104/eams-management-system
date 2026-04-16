package com.zeroone.star.material.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.material.entity.MaterialDO;
import com.zeroone.star.material.mapper.MaterialMapper;
import com.zeroone.star.material.service.IMaterialService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.material.MaterialDTO;
import com.zeroone.star.project.query.j9.material.MaterialRecordQuery;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;

/**
 * <p>
 * 物料表 服务实现类
 * </p>
 *
 * @author fantast
 * @since 2026-03-16
 */
@Service
public class MaterialServiceImpl extends ServiceImpl<MaterialMapper, MaterialDO> implements IMaterialService {

    @Override
    public int updateMaterialState(List<Long> ids, Integer state) {
        LambdaUpdateWrapper<MaterialDO> updateWrapper = new LambdaUpdateWrapper<>();
        updateWrapper.in(MaterialDO::getId, ids)
                .set(MaterialDO::getState, state.equals(1));
        int rows = baseMapper.update(null, updateWrapper);
        return rows > 0 ? 1 : 0;
    }

    @Override
    public PageDTO<MaterialDTO> listAll(MaterialRecordQuery condition) {
        Page<MaterialDO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());
        LambdaQueryWrapper<MaterialDO> wrapper = new LambdaQueryWrapper<>();
        wrapper.orderByDesc(MaterialDO::getEditTime);
        baseMapper.selectPage(page, wrapper);

        List<MaterialDTO> dtoList = page.getRecords().stream().map(item -> {
            MaterialDTO dto = new MaterialDTO();
            BeanUtils.copyProperties(item, dto);
            return dto;
        }).collect(Collectors.toList());

        PageDTO<MaterialDTO> result = new PageDTO<>();
        result.setPageIndex(page.getCurrent());
        result.setPageSize(page.getSize());
        result.setTotal(page.getTotal());
        result.setPages(page.getPages());
        result.setRows(dtoList);
        return result;
    }

    @Override
    public MaterialDTO getMaterialById(Long id) {
        MaterialDO materialDO = baseMapper.selectById(id);
        if (materialDO == null) {
            return null;
        }
        MaterialDTO dto = new MaterialDTO();
        BeanUtils.copyProperties(materialDO, dto);
        return dto;
    }

    @Override
    public Long saveMaterial(MaterialDTO dto) {
        MaterialDO materialDO = new MaterialDO();
        BeanUtils.copyProperties(dto, materialDO);
        LocalDateTime now = LocalDateTime.now();

        if (dto.getId() == null) {
            materialDO.setAddTime(now);
            materialDO.setEditTime(now);
            baseMapper.insert(materialDO);
        } else {
            materialDO.setEditTime(now);
            int rows = baseMapper.updateById(materialDO);
            if (rows == 0) {
                throw new RuntimeException("物料不存在，id：" + dto.getId());
            }
        }
        return materialDO.getId();
    }

}
