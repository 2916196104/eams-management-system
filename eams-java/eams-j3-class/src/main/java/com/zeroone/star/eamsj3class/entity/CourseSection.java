package com.zeroone.star.eamsj3class.entity;

import com.baomidou.mybatisplus.annotation.*;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.util.Date;
import lombok.Data;

/**
 * 课程大纲
 * @TableName course_section
 */
@TableName(value ="course_section")
@Data
public class CourseSection implements Serializable {
    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 所属课程
     */
    @TableField("course_id")
    private Long courseId;

    /**
     * 章节标题
     */
    @TableField("title")
    private String title;

    /**
     * 计划课时数
     */
    @TableField("lesson_count")
    private Integer lessonCount;

    /**
     * 创建人
     */
    @TableField("creator")
    private Long creator;

    /**
     * 编辑人
     */
    @TableField("editor")
    private Long editor;

    /**
     * 添加时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    @TableField("edit_time")
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    @TableLogic
    @TableField("deleted")
    private Integer deleted;

    @TableField(exist = false)
    private static final long serialVersionUID = 1L;
}