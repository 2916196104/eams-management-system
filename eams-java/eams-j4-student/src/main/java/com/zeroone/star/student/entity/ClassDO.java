package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * 班级 DO
 */
@Data
@TableName("class")
public class ClassDO {
    @TableId(type = IdType.AUTO)
    private Long id;

    private String name;

    private Long courseId;

    private Long classroomId;

    private Long creator;

    private Long editor;

    private LocalDateTime addTime;

    private LocalDateTime editTime;

    @TableLogic
    private Integer deleted;

    private Long teacherId;

    private String remark;

    private Integer beOver;

    private LocalDateTime overTime;

    private Long overOperator;

    private LocalDate startDate;

    private LocalDate endDate;

    private Integer plannedStudentCount;

    private Integer plannedLessonCount;

    private Long schoolId;

    private Long orgId;

    private Integer gradeId;
}