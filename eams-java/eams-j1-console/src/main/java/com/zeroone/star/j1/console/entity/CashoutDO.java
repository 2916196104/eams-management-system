package com.zeroone.star.j1.console.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.math.BigDecimal;
import java.util.Date;

/**
 * <p>
 * 请款表
 * </p>
 * @author hxb
 */
@Getter
@Setter
@TableName("cashout")
public class CashoutDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 请款项目名
     */
    private String title;

    /**
     * 请款类型
     */
    private Integer type;

    /**
     * 请款金额
     */
    private BigDecimal amount;

    /**
     * 收款人
     */
    private String payeeName;

    /**
     * 收款账号
     */
    private String account;

    /**
     * 请款信息
     */
    private String info;

    /**
     * 审批状态
     */
    private Integer verifyState;

    /**
     * 审核人
     */
    private Long verifyStaff;

    /**
     * 审核时间
     */
    private Date verifyTime;

    /**
     * 审核备注
     */
    private String verifyRemark;

    /**
     * 申请人
     */
    private Long creator;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 添加时间
     */
    private Date addTime;

    /**
     * 编辑时间
     */
    private Date editTime;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 附件id列表
     */
    private String attachFile;

    /**
     * 创建者所属组织ID
     */
    private Long orgId;
}
