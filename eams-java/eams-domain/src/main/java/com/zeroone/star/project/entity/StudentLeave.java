package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 学员请假
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("student_leave")
public class StudentLeave implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 请假时间
     */
    private LocalDateTime addTime;

    /**
     * 学生外键
     */
    private Long studentId;

    /**
     * 请假课程外键
     */
    private Long lessonId;

    /**
     * 原因
     */
    private String reason;

    /**
     * 状态
     */
    private Integer state;

    /**
     * 取消操作人
     */
    private Long verifyStaff;

    /**
     * 取消时间
     */
    private LocalDateTime verifyTime;

    /**
     * 学生的顾问
     */
    private Long counselor;

    /**
     * 学生所属学校 ID
     */
    private Long schoolId;
}
