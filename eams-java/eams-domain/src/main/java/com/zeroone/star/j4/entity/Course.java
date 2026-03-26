package com.zeroone.star.j4.entity;

import com.baomidou.mybatisplus.annotation.*;
import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * 课程信息表 (对应 zo_eams.sql 中的 course 表)
 */
@Getter
@Setter
@TableName("course")
public class Course implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long subjectId;
    private String name;
    private Integer state;        // 启用状态
    private String info;
    private Long creator;
    private Long editor;
    private LocalDateTime addTime;
    private LocalDateTime editTime;
    private Integer expireMonths;
    private BigDecimal unitPrice;
    private BigDecimal price;      // 售价
    private String unitName;
    private BigDecimal discount;
    private Integer lessonCount;
    private Integer lessonType;
    private String description;

    @TableLogic
    private Boolean deleted;

    private Boolean bookable;
    private Boolean forSale;      // 是否上架
    private Boolean recommend;
    private String cover;         // 封面图
    private LocalDate closeDate;
    private String teacherInfo;
    private String serviceInfo;
    private Integer storage;      // 库存名额
    private Long orgId;
    private BigDecimal salary;
    private String gradeIds;
    private String gradeNames;
}
