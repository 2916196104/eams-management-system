package com.zeroone.star.project.query.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

public class EvaluationQuery {
    @ApiModelProperty(value = "开始时间", example = "2026-01-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束时间", example = "2026-04-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;

    @ApiModelProperty(value = "老师ID",required = false,example = "1")
    private String teacherId;
    @ApiModelProperty(value = "老师姓名",required = false,example = "张三")
    private String teacherName;

    @ApiModelProperty(value = "学生ID",required = false,example = "1")
    private String id;
    @ApiModelProperty(value = "学生姓名",required = false,example = "小明")
    private String name;

}
