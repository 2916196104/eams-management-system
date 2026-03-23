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
 * 财务记录表 数据对象
 * </p>
 *
 * @description 对应数据库表 finance_record，用于财务模块-财务流水记录
 */
@Data
@TableName("finance_record")
public class FinanceRecordDO {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 标题
     */
    @TableField("title")
    private String title;

    /**
     * 金额（退款为负数）
     */
    @TableField("amount")
    private BigDecimal amount;

    /**
     * 收入项类型
     */
    @TableField("item_type")
    private Integer itemType;

    /**
     * 项目ID
     */
    @TableField("item_id")
    private Long itemId;

    /**
     * 经办人ID
     */
    @TableField("operator")
    private Long operator;

    /**
     * 付款人ID
     */
    @TableField("payer")
    private Long payer;

    /**
     * 款项备注
     */
    @TableField("remark")
    private String remark;

    /**
     * 经办日期
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 审核确认状态
     */
    @TableField("verify_state")
    private Integer verifyState;

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
     * 创建者所属组织ID
     */
    @TableField("org_id")
    private Long orgId;
}
