package com.zeroone.star.project.query.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * 获取积分记录查询条件
 */
@Data
@NoArgsConstructor
@AllArgsConstructor
@ApiModel("获取积分记录查询条件")
public class CreditSelectQuery {
    @ApiModelProperty(value = "学生姓名", example = "张三")
    private String student_Name;
    @ApiModelProperty(value = "开始日期", example = "2026-3-15")
    private String begin_time;
    @ApiModelProperty(value = "结束日期", example = "2026-3-16")
    private String end_time;
}
