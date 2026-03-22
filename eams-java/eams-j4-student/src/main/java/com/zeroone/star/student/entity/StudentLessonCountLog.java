package com.zeroone.star.student.entity;

import lombok.Data;

import java.time.LocalDateTime;

/**
 * 消课记录服务DO
 */
@Data
public class StudentLessonCountLog {
    private int id;

    private int studentId;

    private int courseId;

    private int lessonId;

    private int changeCount;

    private int remainingCount;

    private LocalDateTime addTime;

    private String remark;

    private int staff_id;

    private int stage;
}
