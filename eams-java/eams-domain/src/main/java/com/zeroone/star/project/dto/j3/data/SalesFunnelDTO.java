package com.zeroone.star.project.dto.j3.data;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：销售漏斗模型数据传输对象
 * </p>
 * @author yeyue
 * @version 1.0.0
 */
@Data
public class SalesFunnelDTO {
    @ApiModelProperty(value = "阶段编码：0-丢失阶段，10-目标客户阶段，20-潜在客户阶段，30-意向阶段，40-认可阶段，50-签约阶段，60-售后阶段", example = "10")
    private Integer code;

    @ApiModelProperty(value = "阶段名称，与阶段编码对应", example = "目标客户阶段")
    private String name;

    @ApiModelProperty(value = "人数", example = "12")
    private Integer count;
}
