package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;
import java.time.LocalDateTime;

/**
 * 班级学员关系 DO
 */
@Data
@TableName("class_student")
public class ClassStudentDO {
    @TableId(type = IdType.ASSIGN_ID)
    private Long id;

    private Long classId;

    private Long studentId;

    private LocalDateTime addTime;

    private Long creator;

    private Integer reason;

    @TableLogic
    private Integer deleted;

    private String remark;

    private Long consumeCourseId;
}