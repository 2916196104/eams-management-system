package com.zeroone.star.project.vo.j9.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;

/**
 * 兑换申请列表返回VO
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(description = "兑换申请列表返回数据")
public class CreditExchangeVO {

    // 核心必要ID
    @ApiModelProperty(value = "兑换申请ID（前端操作使用）", example = "1001")
    private Long id;

    // 前端展示字段
    @ApiModelProperty(value = "礼品名称", example = "笔记本")
    private String giftName;

    @ApiModelProperty(value = "学生姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "兑换数量", example = "2")
    private Integer num;

    @ApiModelProperty(value = "花费积分", example = "500")
    private String credit;

    @ApiModelProperty(value = "审核状态", example = "待审核")
    private String verifyStateDesc;

    @ApiModelProperty(value = "申请时间", example = "2026-03-15 10:30:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "学校名称", example = "第一实验学校")
    private String schoolName;

    // 审核相关字段：仅非待审核状态展示（默认隐藏）
    @ApiModelProperty(value = "审核人姓名", example = "李四", hidden = true)
    private String verifyStaffName;

    @ApiModelProperty(value = "审核备注", example = "符合兑换规则", hidden = true)
    private String verifyRemark;
}