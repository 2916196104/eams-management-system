package com.zeroone.star.operation.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * 课程体验卡实体
 */
@Getter
@Setter
@TableName("course_trial")
public class CourseTrialDO implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long courseId;

    private String title;

    private Integer quantity;

    private Integer remainingQuantity;

    private Integer lessonCount;

    private Integer expireDays;

    private LocalDate endDate;

    private Integer state;

    private Long creator;

    private Long editor;

    private LocalDateTime addTime;

    private LocalDateTime editTime;

    @TableLogic
    private Integer deleted;

    private Long orgId;
}
