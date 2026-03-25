package com.zeroone.star.j4.entity;

import com.baomidou.mybatisplus.annotation.*;
import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * 学员报名记录表 (对应 zo_eams.sql 中的 student_course 表)
 */
@Getter
@Setter
@TableName("student_course")
public class StudentCourse implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long studentId;
    private Long courseId;
    private Long subjectId;
    private LocalDate startDate;
    private LocalDate expireDate;
    private String remark;

    private Integer countLessonTotal;    // 购买总课次
    private Integer countLessonComplete; // 已上课次
    private Integer countLessonRefund;   // 退款次数

    private BigDecimal courseAmount;     // 套餐金额
    private BigDecimal discountAmount;   // 优惠金额
    private BigDecimal amount;           // 成交/合约金额
    private BigDecimal paidAmount;       // 实付金额

    private Boolean payOff;              // 是否付清
    private Long operator;               // 经手人
    private Long creator;
    private LocalDateTime addTime;       // 录入时间
    private Long editor;
    private LocalDateTime editTime;

    @TableLogic
    private Boolean deleted;             // 删除标记

    private Integer verifyState;         // 审核状态
    private Integer warningTimes;
    private Integer priority;
    private BigDecimal unitPrice;
    private Boolean fromTrial;           // 是否来自体验
    private Long orgId;
}
