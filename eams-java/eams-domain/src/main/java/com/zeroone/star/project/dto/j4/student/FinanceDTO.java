package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：缴欠费与退费传输对象
 * </p>
 */
@Data
public class FinanceDTO {
    @ApiModelProperty(value = "记录ID，缴费时为财务记录ID，退费时为退费单ID", example = "2008418408985583618")
    private Long id;

    @ApiModelProperty(value = "业务类型（1：缴欠费 2：线下退费）", example = "1")
    private Integer type;

    @ApiModelProperty(value = "学员ID", example = "2008418408985583617")
    private Long studentId;

    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "签约记录ID(student_course.id)", example = "2008418408985583601")
    private Long studentCourseId;

    @ApiModelProperty(value = "财务标题", example = "学员补缴学费")
    private String title;

    @ApiModelProperty(value = "金额，缴费为正数；退费申请支持传正数或负数，系统会转成负数落库", example = "1200.00")
    private BigDecimal amount;

    @ApiModelProperty(value = "合约金额", example = "5600.00")
    private BigDecimal contractAmount;

    @ApiModelProperty(value = "实付金额", example = "3200.00")
    private BigDecimal paidAmount;

    @ApiModelProperty(value = "待补缴金额", example = "2400.00")
    private BigDecimal unpaidAmount;

    @ApiModelProperty(value = "是否结清（0：否 1：是）", example = "0")
    private Boolean payOff;

    @ApiModelProperty(value = "经办人ID", example = "1001")
    private Long operator;

    @ApiModelProperty(value = "付款人ID", example = "2008418408985583617")
    private Long payer;

    @ApiModelProperty(value = "备注", example = "学员本次先补缴一半费用")
    private String remark;

    @ApiModelProperty(value = "退款状态（1：已申请 2：审核通过 3：审核驳回 4：已完成）", example = "1")
    private Integer verifyState;

    @ApiModelProperty(value = "审核人ID", example = "1002")
    private Long verifyStaff;

    @ApiModelProperty(value = "审核时间", example = "2026-03-15 17:20:00")
    private LocalDateTime verifyTime;

    @ApiModelProperty(value = "退费课时数", example = "8")
    private Integer refundLessonCount;

    @ApiModelProperty(value = "退费申请时间", example = "2026-03-15 16:20:00")
    private LocalDateTime applyTime;

    @ApiModelProperty(value = "退费完成时间", example = "2026-03-16 10:00:00")
    private LocalDateTime doneTime;

    @ApiModelProperty(value = "业务操作时间", example = "2026-03-15 16:20:00")
    private LocalDateTime operateTime;
}
