package com.zeroone.star.project.query.j9.operation;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;

import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

/**
 * 兑换申请列表查询条件（继承分页父类）
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode(callSuper = true)
@ApiModel(description = "兑换申请列表查询条件")
public class CreditExchangeQuery extends PageQuery {

    @ApiModelProperty(value = "礼品名称（模糊查询）", example = "笔记本")
    private String giftName;

    @ApiModelProperty(value = "审核状态（1=待审核，2=已通过，3=已拒绝）", example = "1")
    private Integer verifyState;

    @ApiModelProperty(value = "开始日期（兑换申请时间≥该日期）", example = "2026-01-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束日期（兑换申请时间≤该日期）", example = "2026-03-31")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;
}