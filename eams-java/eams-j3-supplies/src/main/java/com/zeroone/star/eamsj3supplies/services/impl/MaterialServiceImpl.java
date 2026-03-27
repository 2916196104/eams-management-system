package com.zeroone.star.eamsj3supplies.services.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.eamsj3supplies.mapper.MaterialMapper;
import com.zeroone.star.eamsj3supplies.services.IMaterialService;
import com.zeroone.star.project.DO.Material;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.supplies.MaterialDTO;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * 物料服务实现
 */
@Service
public class MaterialServiceImpl extends ServiceImpl<MaterialMapper, Material> implements IMaterialService {

    @Override
    public JsonVO<PageDTO<MaterialDTO>> getMaterial() {
        // 查询所有物料
        List<Material> materials = list();
        
        // 转换为DTO
        List<MaterialDTO> materialDTOs = new ArrayList<>();
        for (Material material : materials) {
            MaterialDTO dto = new MaterialDTO();
            dto.setMaterialName(material.getName());
            dto.setMaterialCode(material.getCategoryName());
            dto.setMaterialBelong2(material.getSchoolId().toString());
            dto.setMaterialnums(material.getStorage());
            dto.setMaterialstime(material.getEditTime() != null ? material.getEditTime().toString() : "");
            dto.setMaterialstatus(material.getState() != null && material.getState() == 1);
            materialDTOs.add(dto);
        }
        
        // 构建分页DTO
        PageDTO<MaterialDTO> pageDTO = new PageDTO<>();
        pageDTO.setRows(materialDTOs);
        pageDTO.setTotal((long) materialDTOs.size());
        pageDTO.setPageIndex(1L);
        pageDTO.setPageSize((long) materialDTOs.size());
        pageDTO.setPages(1L);
        
        // 构建返回结果
        JsonVO<PageDTO<MaterialDTO>> result = new JsonVO<>();
        result.setData(pageDTO);
        result.setMessage("获取物料列表成功");
        result.setCode(200);
        return result;
    }

    @Override
    public JsonVO<MaterialDTO> saveMaterial(MaterialDTO materialDTO) {
        // 转换DTO为实体
        Material material = new Material();
        material.setName(materialDTO.getMaterialName());
        material.setCategoryName(materialDTO.getMaterialCode());
        material.setSchoolId(Long.valueOf(materialDTO.getMaterialBelong2()));
        material.setStorage(materialDTO.getMaterialnums());
        material.setState(materialDTO.isMaterialstatus() ? 1 : 0);
        material.setEditTime(new Date());
        material.setDeleted(0);
        
        // 保存或更新
        boolean success = saveOrUpdate(material);
        
        // 构建返回结果
        JsonVO<MaterialDTO> result = new JsonVO<>();
        if (success) {
            result.setData(materialDTO);
            result.setMessage("保存物料成功");
            result.setCode(200);
        } else {
            result.setData(materialDTO);
            result.setMessage("保存物料失败");
            result.setCode(500);
        }
        return result;
    }

    @Override
    public JsonVO<MaterialDTO> deleteMaterial(MaterialDTO materialDTO) {
        // 根据物料名称查询
        List<Material> materials = list();
        for (Material material : materials) {
            if (material.getName().equals(materialDTO.getMaterialName())) {
                // 设置删除标记
                material.setDeleted(1);
                boolean success = updateById(material);
                
                // 构建返回结果
                JsonVO<MaterialDTO> result = new JsonVO<>();
                if (success) {
                    result.setData(materialDTO);
                    result.setMessage("删除物料成功");
                    result.setCode(200);
                } else {
                    result.setData(materialDTO);
                    result.setMessage("删除物料失败");
                    result.setCode(500);
                }
                return result;
            }
        }
        
        // 未找到物料
        JsonVO<MaterialDTO> result = new JsonVO<>();
        result.setData(materialDTO);
        result.setMessage("物料不存在");
        result.setCode(404);
        return result;
    }

    @Override
    public JsonVO<MaterialDTO> openMaterial(MaterialDTO materialDTO) {
        // 根据物料名称查询
        List<Material> materials = list();
        for (Material material : materials) {
            if (material.getName().equals(materialDTO.getMaterialName())) {
                // 设置为启用状态
                material.setState(1);
                material.setEditTime(new Date());
                boolean success = updateById(material);
                
                // 构建返回结果
                JsonVO<MaterialDTO> result = new JsonVO<>();
                if (success) {
                    materialDTO.setMaterialstatus(true);
                    result.setData(materialDTO);
                    result.setMessage("启用物料成功");
                    result.setCode(200);
                } else {
                    result.setData(materialDTO);
                    result.setMessage("启用物料失败");
                    result.setCode(500);
                }
                return result;
            }
        }
        
        // 未找到物料
        JsonVO<MaterialDTO> result = new JsonVO<>();
        result.setData(materialDTO);
        result.setMessage("物料不存在");
        result.setCode(404);
        return result;
    }

    @Override
    public JsonVO<MaterialDTO> closeMaterial(MaterialDTO materialDTO) {
        // 根据物料名称查询
        List<Material> materials = list();
        for (Material material : materials) {
            if (material.getName().equals(materialDTO.getMaterialName())) {
                // 设置为禁用状态
                material.setState(0);
                material.setEditTime(new Date());
                boolean success = updateById(material);
                
                // 构建返回结果
                JsonVO<MaterialDTO> result = new JsonVO<>();
                if (success) {
                    materialDTO.setMaterialstatus(false);
                    result.setData(materialDTO);
                    result.setMessage("禁用物料成功");
                    result.setCode(200);
                } else {
                    result.setData(materialDTO);
                    result.setMessage("禁用物料失败");
                    result.setCode(500);
                }
                return result;
            }
        }
        
        // 未找到物料
        JsonVO<MaterialDTO> result = new JsonVO<>();
        result.setData(materialDTO);
        result.setMessage("物料不存在");
        result.setCode(404);
        return result;
    }
}
