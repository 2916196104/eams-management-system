package com.zeroone.star.project.vo.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;

/**
 * 课程章节展示对象
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("课程章节")
public class CourseSectionVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "章节ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "章节标题", example = "第一章 Java基础语法")
    private String title;

    @ApiModelProperty(value = "计划课时数", example = "8")
    private Integer lessonCount;
}
