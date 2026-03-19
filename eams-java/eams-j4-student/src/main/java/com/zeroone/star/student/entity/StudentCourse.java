package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.math.BigDecimal;

/**
 * <p>
 * 描述：学员签约记录实体
 * </p>
 */
@Data
@TableName("student_course")
public class StudentCourse implements Serializable {
    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long studentId;

    private BigDecimal amount;

    private BigDecimal paidAmount;

    private Integer payOff;

    private Long operator;

    private Integer countLessonRefund;

    private Integer deleted;
}
