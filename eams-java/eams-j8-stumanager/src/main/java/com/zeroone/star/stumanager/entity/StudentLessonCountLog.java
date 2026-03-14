package com.zeroone.star.stumanager.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 学员课次变更记录表
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Getter
@Setter
@TableName("student_lesson_count_log")
public class StudentLessonCountLog implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 学员id
     */
    private Long studentId;

    /**
     * 课程id
     */
    private Long courseId;

    /**
     * 课次id
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

    private String remark;


}
