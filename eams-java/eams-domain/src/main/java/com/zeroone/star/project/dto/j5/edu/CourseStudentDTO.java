package com.zeroone.star.project.dto.j5.edu;

import io.swagger.annotations.ApiModelProperty;

import java.util.Date;

public class CourseStudentDTO {
    @ApiModelProperty("主键ID")
    private Long id;

    @ApiModelProperty("课程ID")
    private Long courseId;

    @ApiModelProperty("学生ID")
    private Long studentId;

    @ApiModelProperty("学生类型")
    private int studentType;

    @ApiModelProperty("创建时间")
    private Date createTime;
}
