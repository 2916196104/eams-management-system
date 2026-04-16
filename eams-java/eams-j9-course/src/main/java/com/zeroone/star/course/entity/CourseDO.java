package com.zeroone.star.course.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * 课程实体
 * @author yangxiao
 */
@Getter
@Setter
@TableName("course")
public class CourseDO implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long subjectId;

    private String name;

    private Integer state;

    private String info;

    @TableField(fill = FieldFill.INSERT)
    private Long creator; // 创建人ID

    @TableField(fill = FieldFill.INSERT_UPDATE)
    private Long editor;  // 最后修改人ID

    @TableField(fill = FieldFill.INSERT)
    private LocalDateTime addTime; // 创建时间

    @TableField(fill = FieldFill.INSERT_UPDATE)
    private LocalDateTime editTime; // 最后修改时间

    private Integer expireMonths;

    private BigDecimal unitPrice;

    private BigDecimal price;

    private String unitName;

    private BigDecimal discount;

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

    private BigDecimal salary;

    private String gradeIds;

    private String gradeNames;
}
