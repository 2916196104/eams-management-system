package com.zeroone.star.project.j3.supplies;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.supplies.MaterialDTO;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.ApiModelProperty;

public interface SuppliesApis {

    @ApiModelProperty( value = "获取物料")
    JsonVO<PageDTO<MaterialDTO>> getMaterial();

    @ApiModelProperty( value = "保存修改物料")
    JsonVO<MaterialDTO> saveMaterial(MaterialDTO materialDTO);

    @ApiModelProperty( value = "删除物料")
    JsonVO<MaterialDTO> deleteMaterial(MaterialDTO materialDTO);

    @ApiModelProperty( value = "启用物料")
    JsonVO<MaterialDTO> openMaterial(MaterialDTO materialDTO);

    @ApiModelProperty( value = "禁用物料")
    JsonVO<MaterialDTO> closeMaterial(MaterialDTO materialDTO);
}
