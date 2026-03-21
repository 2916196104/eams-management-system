package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@TableName("student_course")
public class StudentCourseDO {
    @TableId(type = IdType.AUTO)
    private Long id;
    private Long studentId;
    private Long courseId;
    private Long subjectId;
    private LocalDate startDate;
    private LocalDate expireDate;
    private String remark;
    private Integer countLessonTotal;
    private Integer countLessonComplet;
    private Integer countLessonRefund;
    private BigDecimal courseAmount;
    private BigDecimal discountAmount;
    private BigDecimal amount;
    private BigDecimal paidAmount;
    private Integer payOff;
    private Long operator;
    private Long creator;
    private LocalDateTime addTime;
    private Long editor;
    private LocalDateTime editTime;
    private Integer deleted;
    private Integer verifyState;
    private Integer warningTimes;
    private Integer priority;
    private BigDecimal unitPrice;
    private Integer fromTrial;
    private Long orgId;
}