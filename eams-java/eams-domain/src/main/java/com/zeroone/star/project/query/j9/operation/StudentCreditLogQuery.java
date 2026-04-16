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
 * 积分记录查询条件
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode(callSuper = true)
@ApiModel(description = "积分记录查询条件")
public class StudentCreditLogQuery extends PageQuery {

    @ApiModelProperty(value = "学生姓名/学号（模糊查询）", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "手机号（精确查询）", example = "13800138000")
    private String phone;

    @ApiModelProperty(value = "变动原因（模糊查询）", example = "课程打卡")
    private String changeReason;

    @ApiModelProperty(value = "开始日期（变动时间≥该日期）", example = "2026-01-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束日期（变动时间≤该日期）", example = "2026-03-31")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;
}