package com.zeroone.star.project.dataobject.j6.finance;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * <p>
 * 订单 数据对象
 * </p>
 *
 * @description 对应数据库表 shop_order，用于财务模块-订单管理
 */
@Data
@TableName("shop_order")
public class ShopOrderDO {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 订单号
     */
    @TableField("sn")
    private String sn;

    /**
     * 用户ID（家长端账号）
     */
    @TableField("user_id")
    private Long userId;

    /**
     * 学生ID
     */
    @TableField("student_id")
    private Long studentId;

    /**
     * 订单金额
     */
    @TableField("order_money")
    private BigDecimal orderMoney;

    /**
     * 支付金额
     */
    @TableField("pay_money")
    private BigDecimal payMoney;

    /**
     * 订单状态
     */
    @TableField("state")
    private Integer state;

    /**
     * 备注
     */
    @TableField("remark")
    private String remark;

    /**
     * 支付时间
     */
    @TableField("pay_time")
    private LocalDateTime payTime;

    /**
     * 取消时间
     */
    @TableField("cancel_time")
    private LocalDateTime cancelTime;

    /**
     * 是否已退款（0-否，1-是）
     */
    @TableField("refunded")
    private Integer refunded;

    /**
     * 创建人ID
     */
    @TableField("creator")
    private Long creator;

    /**
     * 编辑人ID
     */
    @TableField("editor")
    private Long editor;

    /**
     * 添加时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    @TableField("edit_time")
    private LocalDateTime editTime;

    /**
     * 删除标记（0-未删除，1-已删除）
     */
    @TableLogic
    @TableField("deleted")
    private Integer deleted;

    /**
     * 学生所在学校ID
     */
    @TableField("school_id")
    private Long schoolId;

    /**
     * 学生的顾问ID
     */
    @TableField("counselor")
    private Long counselor;
}
