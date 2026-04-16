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
 * 学员退款记录
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("refund")
public class Refund implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 学生 id
     */
    private Long studentId;

    /**
     * 学生课程关联表 id
     */
    private Long studentCourseId;

    /**
     * 退费办理人
     */
    private Long operator;

    /**
     * 退费金额 负数
     */
    private BigDecimal refundAmount;

    /**
     * 退费课时
     */
    private Integer refundLessonCount;

    /**
     * 退费发起时间
     */
    private LocalDateTime applyTime;

    /**
     * 退费说明
     */
    private String remark;

    /**
     * 退费办完时间
     */
    private LocalDateTime doneTime;

    /**
     * 类型
     */
    private Integer typeNum;

    /**
     * 退款状态
     */
    private Integer verifyState;

    /**
     * 审核时间
     */
    private LocalDateTime verifyTime;

    /**
     * 审核人
     */
    private Long verifyStaff;
}
