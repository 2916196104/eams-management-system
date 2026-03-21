package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.io.Serializable;
import java.math.BigDecimal;
import java.util.Date;

/**
 * 课程基础信息 DO
 * 对应数据库表：course
 */
@Data
@TableName("course")
public class Course implements Serializable {
    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(type = IdType.AUTO)
    private Long id;

    /**
     * 课程名称
     */
    private String course_name;

    /**
     * 科目id
     */
    private Long subject_id;

    /**
     * 课程类型（1-常规课，2-体验课）
     */
    private Integer course_type;

    /**
     * 课程单价
     */
    private BigDecimal price;

    /**
     * 课程总课时
     */
    private Integer total_lesson;

    /**
     * 课程状态（0-下架，1-上架）
     */
    private Integer state;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 创建时间
     */
    private Date add_time;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 编辑时间
     */
    private Date edit_time;

    /**
     * 删除标记（0-未删除，1-已删除）
     */
    @TableLogic
    private Integer deleted;

    /**
     * 所属组织ID
     */
    private Long org_id;
}