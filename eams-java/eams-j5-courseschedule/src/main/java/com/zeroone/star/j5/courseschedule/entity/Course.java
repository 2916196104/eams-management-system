package com.zeroone.star.j5.courseschedule.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
@TableName("course")
public class Course {
    @TableId(type = IdType.ASSIGN_ID)
    private Long id;
    private Long subjectId;
    private String name;
    private Integer state;
    private String info;
    private Long creator;
    private Long editor;
    private LocalDateTime addTime;
    private LocalDateTime editTime;

    @TableLogic
    private Integer deleted;

    private Integer expireMonths;
    private BigDecimal unitPrice;
    private BigDecimal price;
    private String unitName;
    private BigDecimal discount;
    private Integer lessonCount;
    private Integer lessonType;
    private String description;
    private Integer bookable;
    private Integer forSale;
    private Integer recommend;
    private String cover;
}