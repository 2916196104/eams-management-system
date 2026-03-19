package com.zeroone.star.project.query.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
@ApiModel(value = "CourseEnrollmentQuery", description = "课程报名统计查询条件")
public class CourseEnrollmentQuery {

    @ApiModelProperty(value = "学员姓名或电话")
    private String keyword;

    @ApiModelProperty(value = "开始日期-起")
    private LocalDate startDateBegin;

    @ApiModelProperty(value = "开始日期-止")
    private LocalDate startDateEnd;

    @ApiModelProperty(value = "当前页")
    private Integer pageNum = 1;

    @ApiModelProperty(value = "每页大小")
    private Integer pageSize = 30;
}
