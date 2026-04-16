package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 积分商城兑换记录
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("credit_exchange")
public class CreditExchange implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 积分商城礼品 id
     */
    private Long creditMallId;

    /**
     * 学校 id
     */
    private Long schoolId;

    /**
     * 创建人
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
     * 学生 id
     */
    private Long studentId;

    /**
     * 学生账号 id
     */
    private Long userId;

    /**
     * 兑换数量
     */
    private Integer num;

    /**
     * 花费积分
     */
    private String credit;

    /**
     * 审核状态
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
}
