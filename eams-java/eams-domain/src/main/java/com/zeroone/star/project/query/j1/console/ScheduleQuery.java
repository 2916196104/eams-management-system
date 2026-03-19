package com.zeroone.star.project.query.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
@ApiModel(value = "ScheduleQuery", description = "课表日历查询条件")
public class ScheduleQuery {

    @ApiModelProperty(value = "周期（如 2026-03-17 ~ 2026-03-23）起始日期")
    private LocalDate weekStart;

    @ApiModelProperty(value = "周期结束日期")
    private LocalDate weekEnd;

    @ApiModelProperty(value = "班级ID")
    private Long classId;

    @ApiModelProperty(value = "课程ID")
    private Long courseId;

    @ApiModelProperty(value = "老师ID")
    private Long teacherId;

    @ApiModelProperty(value = "学生ID")
    private Long studentId;

    @ApiModelProperty(value = "当前页")
    private Integer pageNum = 1;

    @ApiModelProperty(value = "每页大小")
    private Integer pageSize = 30;
}
