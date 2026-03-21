package com.zeroone.star.project.dto.j5.schedule;


import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/*
* 描述：班级名称查询对象
* */
@Data
public class ClassByNameDTO {

    @ApiModelProperty(value = "班级id",required = false,example = "1")
    private Long id;

    @ApiModelProperty(value = "班级名称",required = false,example = "足球特长班")
    private String className;

    @ApiModelProperty(value = "课程名称",required = false,example = "英语")
    private String courseName;
}
