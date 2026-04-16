package com.zeroone.star.project.dto.j7.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
@ApiModel("礼品状态更新DTO")
public class CreditMallStateUpdateDTO {

    @ApiModelProperty(value = "礼品ID列表", required = true)
    private List<Long> ids;

    @ApiModelProperty(value = "状态：1=启用，0=禁用", example = "1")
    private Integer state;
}