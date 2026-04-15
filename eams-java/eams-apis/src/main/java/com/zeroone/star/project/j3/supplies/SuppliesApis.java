package com.zeroone.star.project.j3.supplies;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.supplies.MaterialDTO;
import com.zeroone.star.project.dto.j3.supplies.MaterialStockChangeDTO;
import com.zeroone.star.project.query.j3.supplies.MaterialRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.supplies.MaterialRecordVO;
import com.zeroone.star.project.vo.j3.supplies.MaterialStockVO;
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

    /**
     * 物料出入库
     * @param materialStockChangeDTO 出入库信息
     * @return 修改结果
     */
    JsonVO<MaterialStockVO> changeMaterialAmount(MaterialStockChangeDTO materialStockChangeDTO);

    /**
     * 物料出入库记录分页查询
     * @param query 查询条件
     * @return 出入库记录分页列表
     */
    JsonVO<PageDTO<MaterialRecordVO>> queryMaterialRecordPage(MaterialRecordQuery query);
}
