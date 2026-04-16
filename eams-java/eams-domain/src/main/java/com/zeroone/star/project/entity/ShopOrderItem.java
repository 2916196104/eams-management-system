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
 * 订单关联物品列表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("shop_order_item")
public class ShopOrderItem implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 订单号
     */
    private Long orderId;

    /**
     * 课程 id
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
