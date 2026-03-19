package com.zeroone.star.project.vo.j3.supplies;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：物料库存及本次出入库结果显示对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 */
@Data
@ApiModel("物料库存显示对象")
public class MaterialStockVO {

    @ApiModelProperty(value = "物料ID", example = "1")
    private Long materialId;

    @ApiModelProperty(value = "物料名称", example = "笔记本")
    private String materialName;

    @ApiModelProperty(value = "当前库存数量", example = "100")
    private Integer currentStorage;
}

