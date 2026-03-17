package com.zeroone.star.project.vo.j6.finance;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
@ApiModel("请款列表行VO")
public class CashoutListVO {

    @ApiModelProperty("请款单ID")
    private Long id;

    @ApiModelProperty("请款项目名")
    private String title;

    @ApiModelProperty("请款类型（数值：1-广告宣传/2-物业费/3-办公耗材/4-水费/5-差旅费/6-其他）")
    private Integer type;

    @ApiModelProperty("请款类型名称")
    private String typeName;

    @ApiModelProperty("申请人ID")
    private Long creator;

    @ApiModelProperty("申请人名称")
    private String creatorName;

    @ApiModelProperty("收款人")
    private String payeeName;

    @ApiModelProperty("收款账号")
    private String account;

    @ApiModelProperty("请款金额")
    private BigDecimal amount;

    @ApiModelProperty("请款说明")
    private String info;

    @ApiModelProperty("审批状态（0-待审核/1-审核通过/2-已驳回/3-已作废）")
    private Integer verifyState;

    @ApiModelProperty("审批状态名称")
    private String verifyStateName;

    @ApiModelProperty("审核备注")
    private String verifyRemark;

    @ApiModelProperty("申请时间")
    private LocalDateTime addTime;
}
