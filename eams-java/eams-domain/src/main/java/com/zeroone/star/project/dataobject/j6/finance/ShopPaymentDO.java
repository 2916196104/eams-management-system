package com.zeroone.star.project.dataobject.j6.finance;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * <p>
 * 支付记录表 数据对象
 * </p>
 *
 * @description 对应数据库表 shop_payment，用于财务模块-支付记录管理
 */
@Data
@TableName("shop_payment")
public class ShopPaymentDO {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 订单ID
     */
    @TableField("order_id")
    private Integer orderId;

    /**
     * 手机端账号ID
     */
    @TableField("user_id")
    private String userId;

    /**
     * 订单编号
     */
    @TableField("order_sn")
    private String orderSn;

    /**
     * 微信交易号
     */
    @TableField("wx_trade_id")
    private String wxTradeId;

    /**
     * 微信支付者openid
     */
    @TableField("wx_openid")
    private String wxOpenid;

    /**
     * 支付金额
     */
    @TableField("pay_money")
    private BigDecimal payMoney;

    /**
     * 添加时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;
}
