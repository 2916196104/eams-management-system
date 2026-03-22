package com.zeroone.star.project.vo.j5.courseplan;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/*
* 含义：班级选项视图对象。
* 适用：所有下拉框场景。
* */
@Data
public class ClassOptionVO {
    @ApiModelProperty(value = "班级id",required = false,example = "1")
    private Long id;

    @ApiModelProperty(value = "班级名称",required = false,example = "足球特长班")
    private String className;

    @ApiModelProperty(value = "课程id 不需要展示，用于对应教师的查询")
    private Long courseId;

    @ApiModelProperty(value = "课程名称",required = false,example = "英语")
    private String courseName;
}
