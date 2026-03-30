package com.zeroone.star.project.query.j6.finance;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

/**
 * 请款列表查询条件
 */
@Data
@ApiModel("请款列表查询条件")
public class CashoutListQuery extends PageQuery {

    @ApiModelProperty(value = "请款项目名",example = "办公用品采购")
    private String title;

    @ApiModelProperty(value = "请款类型",example = "7")
    private Integer type;

    @ApiModelProperty(value = "审核状态（0-待审核，1-审核通过，2-已驳回）",example = "0")
    private Integer verifyState;

    @ApiModelProperty(value = "开始日期",example = "2026-03-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd") // 添加这一行
    private LocalDate startDate;

    @ApiModelProperty(value = "结束日期",example = "2026-03-30")
    @DateTimeFormat(pattern = "yyyy-MM-dd") // 添加这一行
    private LocalDate endDate;

    @ApiModelProperty(value = "申请人ID",example = "2")
    private Long creator;

    @ApiModelProperty(value = "收款人姓名",example = "张三")
    private String payeeName;
}