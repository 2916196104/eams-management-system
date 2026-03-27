package com.zeroone.star.project.dto.j3.supplies;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("物料库存变更结果对象")
public class MaterialStockChangedDTO {
    @ApiModelProperty(value = "物料名称", example = "画笔")
    private String name;

    @ApiModelProperty(value = "变更后库存", example = "120")
    private Integer storage;
}
