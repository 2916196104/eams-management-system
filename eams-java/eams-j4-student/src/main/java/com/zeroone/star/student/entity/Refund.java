package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：退费单实体
 * </p>
 */
@Data
@TableName("refund")
public class Refund implements Serializable {
    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long studentId;

    private Long studentCourseId;

    private Long operator;

    private BigDecimal refundAmount;

    private Integer refundLessonCount;

    private LocalDateTime applyTime;

    private String remark;

    private LocalDateTime doneTime;

    private Integer typeNum;

    private Integer verifyState;

    private LocalDateTime verifyTime;

    private Long verifyStaff;
}
