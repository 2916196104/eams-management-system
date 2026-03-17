package com.zeroone.star.project.query.j6.homework;

import io.swagger.annotations.ApiModelProperty;

public class HomeworkQuery {

    @ApiModelProperty(value = "作业id")
    private Long id;

    @ApiModelProperty(value = "班级id")
    private Long classId;

    @ApiModelProperty(value = "教师id")
    private Long teacherId;


}
