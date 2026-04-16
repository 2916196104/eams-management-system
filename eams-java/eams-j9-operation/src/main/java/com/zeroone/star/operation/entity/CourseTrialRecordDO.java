package com.zeroone.star.operation.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * 课程体验卡领取记录实体
 */
@Getter
@Setter
@TableName("course_trial_record")
public class CourseTrialRecordDO implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long trialId;

    private Long studentId;

    private Long courseId;

    private Long userId;

    private Long studentCourseId;

    private LocalDateTime addTime;

    private LocalDate expiredDate;

    private Integer lessonCount;

    private Long schoolId;

    private Long counselor;
}
