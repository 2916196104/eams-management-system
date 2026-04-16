package com.zeroone.star.project.vo.j6.finance;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
@ApiModel("请款单VO")
public class CashoutListVO {

    @ApiModelProperty("请款单ID")
    private Long id;

    @ApiModelProperty("请款项目名")
    private String title;

    @ApiModelProperty("请款类型")
    private Integer type;

    @ApiModelProperty("申请人")
    private String creatorName;

    @ApiModelProperty("收款人")
    private String payeeName;

    @ApiModelProperty("收款账号")
    private String account;

    @ApiModelProperty("请款金额")
    private BigDecimal amount;

    @ApiModelProperty("请款信息")
    private String info;

    @ApiModelProperty("审批状态")
    private Integer verifyState;

    @ApiModelProperty("审核备注")
    private String verifyRemark;

    @ApiModelProperty("申请时间")
    private LocalDateTime addTime;
}
