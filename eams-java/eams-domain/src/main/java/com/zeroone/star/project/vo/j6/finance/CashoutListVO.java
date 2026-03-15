package com.zeroone.star.project.vo.j6.finance;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * 请款列表行 VO（前端展示）
 */
@Data
@ApiModel("请款列表行VO")
public class CashoutListVO {

    @ApiModelProperty("请款单ID")
    private Long id;

    @ApiModelProperty("请款项目名")
    private String title;

    @ApiModelProperty("请款类型（数值：1-广告宣传/2-物业费/...）")
    private Integer type;

    @ApiModelProperty("请款类型名称（如：广告宣传）")
    private String typeName;

    @ApiModelProperty("申请人名称（可由 creator 关联人员表后填充）")
    private String creatorName;

    @ApiModelProperty("收款人")
    private String payeeName;

    @ApiModelProperty("收款账号")
    private String account;

    @ApiModelProperty("请款金额")
    private BigDecimal amount;

    @ApiModelProperty("请款信息")
    private String info;

    @ApiModelProperty("审批状态（数值：0-待审核/1-审核通过/2-已驳回）")
    private Integer verifyState;

    @ApiModelProperty("审批状态名称（待审核/审核通过/已驳回）")
    private String verifyStateName;

    @ApiModelProperty("审核备注")
    private String verifyRemark;

    @ApiModelProperty("申请时间（add_time）")
    private LocalDateTime addTime;
}