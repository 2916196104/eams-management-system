package com.zeroone.star.eamsj3supplies.services;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.DO.Material;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.supplies.MaterialDTO;
import com.zeroone.star.project.vo.JsonVO;

/**
 * 物料服务接口
 */
public interface IMaterialService extends IService<Material> {
    /**
     * 获取物料列表
     * @return 物料列表
     */
    JsonVO<PageDTO<MaterialDTO>> getMaterial();

    /**
     * 保存/修改物料
     * @param materialDTO 物料DTO
     * @return 保存结果
     */
    JsonVO<MaterialDTO> saveMaterial(MaterialDTO materialDTO);

    /**
     * 删除物料
     * @param materialDTO 物料DTO
     * @return 删除结果
     */
    JsonVO<MaterialDTO> deleteMaterial(MaterialDTO materialDTO);

    /**
     * 启用物料
     * @param materialDTO 物料DTO
     * @return 启用结果
     */
    JsonVO<MaterialDTO> openMaterial(MaterialDTO materialDTO);

    /**
     * 禁用物料
     * @param materialDTO 物料DTO
     * @return 禁用结果
     */
    JsonVO<MaterialDTO> closeMaterial(MaterialDTO materialDTO);
}
