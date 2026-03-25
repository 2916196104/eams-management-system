package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 消课记录服务DO
 */
@Data
public class StudentLessonCountLog {
    @TableId(type = IdType.AUTO)
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

    private int staffId;
}
