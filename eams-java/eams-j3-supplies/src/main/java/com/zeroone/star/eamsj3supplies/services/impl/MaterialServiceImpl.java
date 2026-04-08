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
        try {
            // 查询所有物料
            List<Material> materials = list();
            
            // 转换为DTO
            List<MaterialDTO> materialDTOs = new ArrayList<>();
            for (Material material : materials) {
                MaterialDTO dto = new MaterialDTO();
                dto.setMaterialId(material.getId());
                dto.setMaterialName(material.getName());
                dto.setMaterialCode(material.getCategoryName());
                // 检查schoolId是否为null
                dto.setMaterialBelong2(material.getSchoolId() != null ? material.getSchoolId().toString() : "");
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
        } catch (Exception e) {
            // 捕获所有异常，避免500错误
            JsonVO<PageDTO<MaterialDTO>> result = new JsonVO<>();
            result.setData(new PageDTO<>());
            result.setMessage("获取物料列表失败：" + e.getMessage());
            result.setCode(500);
            return result;
        }
    }

    @Override
    public JsonVO<MaterialDTO> saveMaterial(MaterialDTO materialDTO) {
        try {
            // 检查materialDTO是否为null
            if (materialDTO == null) {
                JsonVO<MaterialDTO> result = new JsonVO<>();
                result.setData(materialDTO);
                result.setMessage("参数不能为空");
                result.setCode(400);
                return result;
            }
            
            // 转换DTO为实体
            Material material = new Material();
            material.setId(materialDTO.getMaterialId());
            material.setName(materialDTO.getMaterialName());
            material.setCategoryName(materialDTO.getMaterialCode());
            material.setCategoryId(1L); // 默认值
            // 检查materialBelong2是否为空
            if (materialDTO.getMaterialBelong2() != null && !materialDTO.getMaterialBelong2().isEmpty()) {
                material.setSchoolId(Long.valueOf(materialDTO.getMaterialBelong2()));
            } else {
                material.setSchoolId(1L); // 默认值
            }
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
        } catch (Exception e) {
            // 捕获所有异常，避免500错误
            JsonVO<MaterialDTO> result = new JsonVO<>();
            result.setData(materialDTO);
            result.setMessage("保存物料失败：" + e.getMessage());
            result.setCode(500);
            return result;
        }
    }

    @Override
    public JsonVO<MaterialDTO> deleteMaterial(MaterialDTO materialDTO) {
        try {
            // 检查materialDTO是否为null
            if (materialDTO == null) {
                JsonVO<MaterialDTO> result = new JsonVO<>();
                result.setData(materialDTO);
                result.setMessage("参数不能为空");
                result.setCode(400);
                return result;
            }
            
            // 根据物料名称查询
            List<Material> materials = list();
            for (Material material : materials) {
                // 检查material.getName()是否为null
                if (material.getName() != null && material.getName().equals(materialDTO.getMaterialName())) {
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
        } catch (Exception e) {
            // 捕获所有异常，避免500错误
            JsonVO<MaterialDTO> result = new JsonVO<>();
            result.setData(materialDTO);
            result.setMessage("删除物料失败：" + e.getMessage());
            result.setCode(500);
            return result;
        }
    }

    @Override
    public JsonVO<MaterialDTO> openMaterial(MaterialDTO materialDTO) {
        try {
            // 检查materialDTO是否为null
            if (materialDTO == null) {
                JsonVO<MaterialDTO> result = new JsonVO<>();
                result.setData(materialDTO);
                result.setMessage("参数不能为空");
                result.setCode(400);
                return result;
            }
            
            // 根据物料名称查询
            List<Material> materials = list();
            for (Material material : materials) {
                // 检查material.getName()是否为null
                if (material.getName() != null && material.getName().equals(materialDTO.getMaterialName())) {
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
        } catch (Exception e) {
            // 捕获所有异常，避免500错误
            JsonVO<MaterialDTO> result = new JsonVO<>();
            result.setData(materialDTO);
            result.setMessage("启用物料失败：" + e.getMessage());
            result.setCode(500);
            return result;
        }
    }

    @Override
    public JsonVO<MaterialDTO> closeMaterial(MaterialDTO materialDTO) {
        try {
            // 检查materialDTO是否为null
            if (materialDTO == null) {
                JsonVO<MaterialDTO> result = new JsonVO<>();
                result.setData(materialDTO);
                result.setMessage("参数不能为空");
                result.setCode(400);
                return result;
            }
            
            // 根据物料名称查询
            List<Material> materials = list();
            for (Material material : materials) {
                // 检查material.getName()是否为null
                if (material.getName() != null && material.getName().equals(materialDTO.getMaterialName())) {
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
        } catch (Exception e) {
            // 捕获所有异常，避免500错误
            JsonVO<MaterialDTO> result = new JsonVO<>();
            result.setData(materialDTO);
            result.setMessage("操作失败：" + e.getMessage());
            result.setCode(500);
            return result;
        }
    }
}
