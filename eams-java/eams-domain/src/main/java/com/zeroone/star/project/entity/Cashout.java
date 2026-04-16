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
 * 样本（请款）
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("cashout")
public class Cashout implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
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
    private LocalDateTime verifyTime;

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
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 附件 id 列表
     */
    private String attachFile;

    /**
     * 创建者所属组织 ID
     */
    private Long orgId;
}
