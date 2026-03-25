package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * 课程 DO
 */
@Data
@TableName("course")
public class CourseDO {
    @TableId(type = IdType.AUTO)
    private Long id;

    private Long subjectId;

    private String name;

    private Integer state;

    private String info;

    private Long creator;

    private Long editor;

    private LocalDateTime addTime;

    private LocalDateTime editTime;

    private Integer expireMonths;

    private java.math.BigDecimal unitPrice;

    private java.math.BigDecimal price;

    private String unitName;

    private java.math.BigDecimal discount;

    private Integer lessonCount;

    private Integer lessonType;

    private String description;

    @TableLogic
    private Integer deleted;

    private Integer bookable;

    private Integer forSale;

    private Integer recommend;

    private String cover;

    private LocalDate closeDate;

    private String teacherInfo;

    private String serviceInfo;

    private Integer storage;

    private Long orgId;

    private java.math.BigDecimal salary;

    private String gradeIds;

    private String gradeNames;
}