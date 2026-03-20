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
 * 描述：财务流水实体
 * </p>
 */
@Data
@TableName("finance_record")
public class FinanceRecord implements Serializable {
    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private String title;

    private BigDecimal amount;

    private Integer itemType;

    private Long itemId;

    private Long operator;

    private Long payer;

    private String remark;

    private LocalDateTime addTime;

    private Integer verifyState;

    private Long verifyStaff;

    private LocalDateTime verifyTime;
}
