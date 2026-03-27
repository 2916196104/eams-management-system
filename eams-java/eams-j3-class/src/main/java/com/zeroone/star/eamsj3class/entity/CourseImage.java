package com.zeroone.star.eamsj3class.entity;

import com.baomidou.mybatisplus.annotation.TableName;

import java.io.Serializable;
import java.time.LocalDateTime;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 课程介绍图片
 * </p>
 *
 * @author heavydrink
 * @since 2026-03-23
 */
@Getter
@Setter
@TableName("course_image")
public class CourseImage implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 所属课程
     */
    private Long courseId;

    /**
     * 图片地址
     */
    private String imageUrl;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    private Boolean deleted;


}
