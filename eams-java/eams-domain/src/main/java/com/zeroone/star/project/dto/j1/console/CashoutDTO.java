package com.zeroone.star.project.dto.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
@ApiModel("我的请款DTO")
public class CashoutDTO {

    @ApiModelProperty(value = "主键ID")
    private Long id;

    @ApiModelProperty(value = "请款项目")
    private String title;

    @ApiModelProperty(value = "款项类型值")
    private Integer type;

    @ApiModelProperty(value = "款项类型名称")
    private String typeName;

    @ApiModelProperty(value = "申请人ID")
    private Long creator;

    @ApiModelProperty(value = "申请人")
    private String applicantName;

    @ApiModelProperty(value = "收款人")
    private String payeeName;

    @ApiModelProperty(value = "请款金额")
    private BigDecimal amount;

    @ApiModelProperty(value = "申请时间")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "收款账号")
    private String account;

    @ApiModelProperty(value = "请款说明")
    private String info;

    @ApiModelProperty(value = "审核状态值")
    private Integer verifyState;

    @ApiModelProperty(value = "审核状态名称")
    private String verifyStateName;

    @ApiModelProperty(value = "审核人ID")
    private Long verifyStaff;

    @ApiModelProperty(value = "审核人名称")
    private String verifyStaffName;

    @ApiModelProperty(value = "审核时间")
    private LocalDateTime verifyTime;

    @ApiModelProperty(value = "审核备注")
    private String verifyRemark;

    @ApiModelProperty(value = "审核信息")
    private String verifyInfo;

    @ApiModelProperty(value = "附件")
    private String attachFile;
}
