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
 * 请款记录 数据对象
 * </p>
 *
 * @description 对应数据库表 cashout，用于财务模块-请款申请管理
 */
@Data
@TableName("cashout")
public class CashoutDO {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 请款项目名
     */
    @TableField("title")
    private String title;

    /**
     * 请款类型
     */
    @TableField("type")
    private Integer type;

    /**
     * 请款金额
     */
    @TableField("amount")
    private BigDecimal amount;

    /**
     * 收款人姓名
     */
    @TableField("payee_name")
    private String payeeName;

    /**
     * 收款账号
     */
    @TableField("account")
    private String account;

    /**
     * 请款信息
     */
    @TableField("info")
    private String info;

    /**
     * 审批状态
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
     * 申请人ID
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
     * 附件ID列表（多个用逗号分隔）
     */
    @TableField("attach_file")
    private String attachFile;

    /**
     * 创建者所属组织ID
     */
    @TableField("org_id")
    private Long orgId;
}
