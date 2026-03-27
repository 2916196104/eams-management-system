package com.zeroone.star.project.vo.j5.classmanager;

import io.swagger.annotations.ApiModelProperty;

public class ClassOptionsVO {

    @ApiModelProperty(value = "班级名", example = "计算机四班")
    private String className;

    @ApiModelProperty(value = "课程", example = "java")
    private String course;

    @ApiModelProperty(value = "操作", example = "添加")
    private String operation;

}
