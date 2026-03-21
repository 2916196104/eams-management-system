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
 * 订单关联物品列表 数据对象
 * </p>
 *
 * @description 对应数据库表 shop_order_item，用于财务模块-订单明细
 */
@Data
@TableName("shop_order_item")
public class ShopOrderItemDO {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 订单ID
     */
    @TableField("order_id")
    private Long orderId;

    /**
     * 课程/物品ID
     */
    @TableField("item_id")
    private Long itemId;

    /**
     * 物品名称
     */
    @TableField("item_name")
    private String itemName;

    /**
     * 购买物品类型（1-课程）
     */
    @TableField("item_type")
    private Integer itemType;

    /**
     * 购买价格
     */
    @TableField("price")
    private BigDecimal price;

    /**
     * 购买数量
     */
    @TableField("quantity")
    private Integer quantity;

    /**
     * 图片URL
     */
    @TableField("cover")
    private String cover;

    /**
     * 添加时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;
}
