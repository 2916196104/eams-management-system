package com.zeroone.star.project.dto.j3.supplies;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class MaterialStockChangeDTO {

    @ApiModelProperty(value = "物料id", required = true )
    private Long materialId;

    @ApiModelProperty(value = "变动数量", required = true)
    private Integer amount;

    @ApiModelProperty(value = "变动原因说明", required = true)
    private String reason;

    @ApiModelProperty(value = "变动类型", required = true, example = "1入库2出库3积分商城出库 ")
    private Integer changeType;
}
