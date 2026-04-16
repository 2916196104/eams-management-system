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
 * 支付记录表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("shop_payment")
public class ShopPayment implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 订单 id
     */
    private Integer orderId;

    /**
     * 手机端账号 id
     */
    private String userId;

    /**
     * 订单编号
     */
    private String orderSn;

    /**
     * 微信交易号
     */
    private String wxTradeId;

    /**
     * 微信支付者 openid
     */
    private String wxOpenid;

    /**
     * 支付金额
     */
    private BigDecimal payMoney;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;
}
