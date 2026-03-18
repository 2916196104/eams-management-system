package com.zeroone.star.project.dto.j6.homework;

import io.swagger.annotations.ApiModelProperty;

/**
 * 作业管理
 */
public class HomeworkDTO {

    @ApiModelProperty(value = "作业id")
    private Long id;

    @ApiModelProperty(value = "作业名称")
    private String name;

    @ApiModelProperty(value = "班级id")
    private Long classId;

    @ApiModelProperty(value = "教师id")
    private Long teacherId;


}
