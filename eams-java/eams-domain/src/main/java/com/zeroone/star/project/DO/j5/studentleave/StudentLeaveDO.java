package com.zeroone.star.project.DO.j5.studentleave;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;

import lombok.*;

/**
 * <p>
 * 学员请假
 * </p>
 *
 * @author xiaoke
 * @since 2026-03-22
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@TableName("student_leave")
public class StudentLeaveDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
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
     * 学生所属学校ID
     */
    private Long schoolId;

}
