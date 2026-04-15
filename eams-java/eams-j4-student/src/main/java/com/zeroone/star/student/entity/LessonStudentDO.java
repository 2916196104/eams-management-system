package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.time.LocalDateTime;

@Data
@TableName("lesson_student")
public class LessonStudentDO {
    @TableId(type = IdType.AUTO)
    private Long id;
    private Long lessonId;
    private Integer classId;
    private Long studentId;
    private Integer decLessonCount;
    private Integer lessonCount;
    private Long teacherId;
    private LocalDateTime signTime;
    private Integer signType;
    private Integer signState;
    private Integer score;
    private String evaluation;
    private LocalDateTime evaluateTime;
    private Long evaluateTeacher;
    private Long consumeCourseId;
    private Long consumeStudentCourseId;
    private Long counselor;
    private LocalDateTime addTime;
    private Long orgId;
}