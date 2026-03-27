package com.zeroone.star.project.DO;

import javax.validation.constraints.NotNull;

import io.swagger.annotations.ApiModelProperty;

import java.io.Serializable;

/**
 * 课程关联表
 *
 * @TableName course_link
 */
public class CourseLink implements Serializable {

    /**
     * 主键
     */
    @NotNull(message = "[主键]不能为空")
    @ApiModelProperty("主键")
    private Long id;

    /**
     * 课程id
     */
    @NotNull(message = "[课程id]不能为空")
    @ApiModelProperty("课程id")
    private Long courseId;

    /**
     * 关联课程id
     */
    @NotNull(message = "[关联课程id]不能为空")
    @ApiModelProperty("关联课程id")
    private Long linkedId;

    /**
     * 主键
     */
    private void setId(Long id) {
        this.id = id;
    }

    /**
     * 课程id
     */
    private void setCourseId(Long courseId) {
        this.courseId = courseId;
    }

    /**
     * 关联课程id
     */
    private void setLinkedId(Long linkedId) {
        this.linkedId = linkedId;
    }

    /**
     * 主键
     */
    private Long getId() {
        return this.id;
    }

    /**
     * 课程id
     */
    private Long getCourseId() {
        return this.courseId;
    }

    /**
     * 关联课程id
     */
    private Long getLinkedId() {
        return this.linkedId;
    }
}
