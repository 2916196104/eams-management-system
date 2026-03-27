package com.zeroone.star.eamsj3class.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 订单关联物品列表
 * </p>
 *
 * @author heavydrink
 * @since 2026-03-23
 */
@Getter
@Setter
@TableName("shop_order_item")
public class ShopOrderItem implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 订单号
     */
    private Long orderId;

    /**
     * 课程id
     */
    private Long itemId;

    /**
     * 名称
     */
    private String itemName;

    /**
     * 购买物品类型 1 课程
     */
    private Integer itemType;

    /**
     * 购买价格
     */
    private BigDecimal price;

    /**
     * 购买数量
     */
    private Integer quantity;

    /**
     * 图片
     */
    private String cover;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;


}
