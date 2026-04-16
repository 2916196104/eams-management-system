package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * <p>
 * 财务记录表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("finance_record")
public class FinanceRecord implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 标题
     */
    private String title;

    /**
     * 金额，退款为负数
     */
    private BigDecimal amount;

    /**
     * 收入项类型
     */
    private Integer itemType;

    /**
     * 项目 id
     */
    private Long itemId;

    /**
     * 经办人 id
     */
    private Long operator;

    /**
     * 付款人 id
     */
    private Long payer;

    /**
     * 款项备注
     */
    private String remark;

    /**
     * 经办日期
     */
    private LocalDateTime addTime;

    /**
     * 审核确认状态
     */
    private Integer verifyState;

    /**
     * 审核人
     */
    private Long verifyStaff;

    /**
     * 审核时间
     */
    private LocalDateTime verifyTime;

    /**
     * 审核备注
     */
    private String verifyRemark;

    /**
     * 创建者所属组织 ID
     */
    private Long orgId;
}
