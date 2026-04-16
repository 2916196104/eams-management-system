package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 学员课次变更记录表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("student_lesson_count_log")
public class StudentLessonCountLog implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 学员 id
     */
    private Long studentId;

    /**
     * 课程 id
     */
    private Long courseId;

    /**
     * 课次 id
     */
    private Long lessonId;

    /**
     * 变更课次数
     */
    private Integer changeCount;

    /**
     * 剩余数量
     */
    private Integer remainingCount;

    /**
     * 操作人
     */
    private Long staffId;

    /**
     * 时间
     */
    private LocalDateTime addTime;

    /**
     * 变更阶段
     */
    private Integer stage;

    /**
     * 备注
     */
    private String remark;
}
