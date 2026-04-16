package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.math.BigDecimal;

/**
 * <p>
 * 课时老师关联表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("lesson_teacher")
public class LessonTeacher implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 课程 id
     */
    private Long lessonId;

    /**
     * 学员 id
     */
    private Long teacherId;

    /**
     * 课时费
     */
    private BigDecimal commission;

    /**
     * 1 上课老师 2 助教
     */
    private Integer typeNum;
}
