package com.zeroone.star.project.dto.j3.supplies;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.Min;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

@Data
@ApiModel("物料出入库变更对象")
public class MaterialStockChangeDTO {

    @NotNull(message = "物料id不能为空")
    @ApiModelProperty(value = "物料id", required = true )
    private Long materialId;

    @NotNull(message = "变动数量不能为空")
    @Min(value = 1, message = "变动数量必须大于0")
    @ApiModelProperty(value = "变动数量", required = true)
    private Integer amount;

    @NotBlank(message = "变动原因说明不能为空")
    @ApiModelProperty(value = "变动原因说明", required = true)
    private String reason;

    @NotNull(message = "变动类型不能为空")
    @ApiModelProperty(value = "变动类型", required = true, example = "1入库2出库3积分商城出库 ")
    private Integer changeType;
}
