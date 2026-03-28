package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.Date;

@Data
public class CourseStudentDTO {
    @ApiModelProperty("主键ID")
    private Long id;

    @ApiModelProperty("课程ID")
    private Long courseId;

    @ApiModelProperty("学生ID")
    private Long studentId;
    @ApiModelProperty("学生名称/电话")
    private String studentNameOrPhone;

    @ApiModelProperty("学生类型")
    private int studentType;


}
