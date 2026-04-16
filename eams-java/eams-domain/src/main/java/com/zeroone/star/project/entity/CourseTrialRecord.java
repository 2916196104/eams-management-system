package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 课程体验卡领取记录
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("course_trial_record")
public class CourseTrialRecord implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 卡 ID
     */
    private Long trialId;

    /**
     * 学生 ID
     */
    private Long studentId;

    /**
     * 课程 ID
     */
    private Long courseId;

    /**
     * 学生账号 id
     */
    private Long userId;

    /**
     * 生成的学生课程关联 ID
     */
    private Long studentCourseId;

    /**
     * 领取时间
     */
    private LocalDateTime addTime;

    /**
     * 到期时间
     */
    private LocalDate expiredDate;

    /**
     * 领取到数量预约后减少
     */
    private Integer lessonCount;

    /**
     * 学生所属学校 ID
     */
    private Long schoolId;

    /**
     * 学生的顾问
     */
    private Long counselor;
}
