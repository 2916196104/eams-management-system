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
 * 订单退款记录
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("shop_order_refund")
public class ShopOrderRefund implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 退款编号
     */
    private String refundSn;

    /**
     * 订单 id
     */
    private Long orderId;

    /**
     * 学生端账号 id
     */
    private Long userId;

    /**
     * 学生 id
     */
    private Long studentId;

    /**
     * 物品名称
     */
    private String itemNames;

    /**
     * 退款金额
     */
    private BigDecimal refundMoney;

    /**
     * 原因类型
     */
    private Integer reasonType;

    /**
     * 原因描述
     */
    private String reason;

    /**
     * 状态
     */
    private Integer state;

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
     * 微信退款 id
     */
    private String wxRefundId;

    /**
     * 申请时间
     */
    private LocalDateTime addTime;

    /**
     * 执行退款人 ID
     */
    private Long operatorId;

    /**
     * 执行退款时间
     */
    private LocalDateTime operationTime;

    /**
     * 执行退款人姓名
     */
    private String operatorName;

    /**
     * 所属 order 的学校 ID
     */
    private Long schoolId;
}
