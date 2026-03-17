package com.zeroone.star.project.dto.j8.stumanager;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@Data
public class PayOverdueDTO {
    /**
     * 缴费金额
     */
    @ApiModelProperty(value = "缴费金额",required = true,example = "100")
    private BigDecimal payAmount;

    /**
     * 收款经手人
     */
    @ApiModelProperty(value = "收款经手人，默认值为管理员1", example = "1")
    private Long operator;

}
