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
 * 订单退款记录 数据对象
 * </p>
 *
 * @description 对应数据库表 shop_order_refund，用于财务模块-订单退款管理
 */
@Data
@TableName("shop_order_refund")
public class ShopOrderRefundDO {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 退款编号
     */
    @TableField("refund_sn")
    private String refundSn;

    /**
     * 订单ID
     */
    @TableField("order_id")
    private Long orderId;

    /**
     * 学生端账号ID
     */
    @TableField("user_id")
    private Long userId;

    /**
     * 学生ID
     */
    @TableField("student_id")
    private Long studentId;

    /**
     * 物品名称（多个用逗号分隔）
     */
    @TableField("item_names")
    private String itemNames;

    /**
     * 退款金额
     */
    @TableField("refund_money")
    private BigDecimal refundMoney;

    /**
     * 原因类型
     */
    @TableField("reason_type")
    private Integer reasonType;

    /**
     * 原因描述
     */
    @TableField("reason")
    private String reason;

    /**
     * 退款状态
     */
    @TableField("state")
    private Integer state;

    /**
     * 审核人ID
     */
    @TableField("verify_staff")
    private Long verifyStaff;

    /**
     * 审核时间
     */
    @TableField("verify_time")
    private LocalDateTime verifyTime;

    /**
     * 审核备注
     */
    @TableField("verify_remark")
    private String verifyRemark;

    /**
     * 微信退款ID
     */
    @TableField("wx_refund_id")
    private String wxRefundId;

    /**
     * 申请时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 执行退款人ID
     */
    @TableField("operator_id")
    private Long operatorId;

    /**
     * 执行退款时间
     */
    @TableField("operation_time")
    private LocalDateTime operationTime;

    /**
     * 执行退款人姓名
     */
    @TableField("operator_name")
    private String operatorName;

    /**
     * 所属订单的学校ID
     */
    @TableField("school_id")
    private Long schoolId;
}
