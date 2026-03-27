package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

/**
 * <p>
 * 描述：请款记录视图对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 康康舞曲
 * @version 1.0.0
 */
@ApiModel("请款记录视图对象")
@Data
public class MyPaymentVO {

    @ApiModelProperty(value = "请款记录ID", example = "4001")
    private Long id;

    @ApiModelProperty(value = "请款项目", example = "2024年3月市场推广费用")
    private String title;

    @ApiModelProperty(value = "款项类型", example = "1")
    private Integer type;

    @ApiModelProperty(value = "申请人", example = "王老师")
    private String applicantName;

    @ApiModelProperty(value = "收款人", example = "张三")
    private String payeeName;

    @ApiModelProperty(value = "请款金额", example = "5000.00")
    private BigDecimal amount;

    @ApiModelProperty(value = "申请时间", example = "2024-03-15 09:00:00")
    private String applyTime;

    @ApiModelProperty(value = "收款账号", example = "6222021234567890")
    private String account;

    @ApiModelProperty(value = "请款说明", example = "用于线下推广活动")
    private String info;

    @ApiModelProperty(value = "审核状态", example = "1")
    private Integer verifyState;

    @ApiModelProperty(value = "审核信息（审核备注）", example = "同意报销")
    private String verifyRemark;
}
