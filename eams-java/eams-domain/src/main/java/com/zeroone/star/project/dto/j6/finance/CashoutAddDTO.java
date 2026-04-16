package com.zeroone.star.project.dto.j6.finance;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.math.BigDecimal;

/**
 * 报存请款时添加的
 */
@Data
@ApiModel("请款新增DTO")
public class CashoutAddDTO {

    @NotBlank(message = "请款项目名不能为空")
    @ApiModelProperty(value = "请款项目名", required = true)
    private String title;

    @NotNull(message = "请款类型不能为空")
    @ApiModelProperty(value = "请款类型（1-广告宣传/2-物业费/3-办公耗材/4-水费/5-差旅费/6-其他）", required = true)
    private Integer type;

    @NotNull(message = "请款金额不能为空")
    @ApiModelProperty(value = "请款金额", required = true)
    private BigDecimal amount;

    @ApiModelProperty(value = "收款人")
    private String payeeName;

    @ApiModelProperty(value = "收款账号")
    private String account;

    @ApiModelProperty(value = "请款说明")
    private String info;

    @ApiModelProperty(value = "附件ID列表（多个用逗号分隔）")
    private String attachFile;
}
