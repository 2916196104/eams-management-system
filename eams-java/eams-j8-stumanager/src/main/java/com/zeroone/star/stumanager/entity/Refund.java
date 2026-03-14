package com.zeroone.star.stumanager.entity;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 学员退款记录
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Getter
@Setter
public class Refund implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 学生id
     */
    private Long studentId;

    /**
     * 学生课程关联表id
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
