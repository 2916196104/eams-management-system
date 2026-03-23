package com.zeroone.star.eamsj3class.entity;

import com.baomidou.mybatisplus.annotation.TableName;

import java.io.Serializable;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 课程关联表
 * </p>
 *
 * @author heavydrink
 * @since 2026-03-23
 */
@Getter
@Setter
@TableName("course_link")
public class CourseLink implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 课程id
     */
    private Long courseId;

    /**
     * 关联课程id
     */
    private Long linkedId;


}
