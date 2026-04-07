package com.zeroone.star.j5.courseschedule.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@TableName("class")
public class EduClass {
    @TableId(type = IdType.ASSIGN_ID)
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
    private Long gradeId;
}