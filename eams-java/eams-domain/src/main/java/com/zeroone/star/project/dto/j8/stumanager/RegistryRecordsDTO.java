package com.zeroone.star.project.dto.j8.stumanager;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
public class RegistryRecordsDTO {

    /**
     * 添加时间
     */
    @ApiModelProperty(value = "添加时间", example = "2023-01-01 10:20")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm")
    private LocalDateTime addTime;

    /**
     * 课程名
     */
    @ApiModelProperty(value = "课程名", example = "粤语")
    private String name;

    /**
     * 科目名
     */
    @ApiModelProperty(value = "科目名", example = "数学")
    private String subjectName;

    /**
     * 类型
     */
    @ApiModelProperty(value = "类型【1新签，2续签】", example = "1")
    private Integer type;

    /**
     * 购买课时
     */
    @ApiModelProperty(value = "购买课时", example = "15")
    private Integer countLessonTotal;

    /**
     * 单价
     */
    @ApiModelProperty(value = "单价", example = "100")
    private BigDecimal unitPrice;

    /**
     * 课程价格
     */
    @ApiModelProperty(value = "课程价格", example = "1200")
    private BigDecimal amount;

    /**
     * 课程优惠
     */
    @ApiModelProperty(value = "课程优惠", example = "0.05")
    private BigDecimal discountAmount;

    /**
     * 实付金额
     */
    @ApiModelProperty(value = "实付金额", example = "1222")
    private BigDecimal paidAmount;

    /**
     * 欠费
     */
    @ApiModelProperty(value = "欠费", example = "5")
    private BigDecimal payOverdue;

    /**
     * 开始时间
     */
    @ApiModelProperty(value = "开始时间", example = "2023-01-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    /**
     * 有效期至
     */
    @ApiModelProperty(value = "有效期至", example = "2023-01-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate expireDate;

    /**
     * 审核状态
     */
    @ApiModelProperty(value = "审核状态【1审核中，2已审核】", example = "1")
    private Integer verifyState;

    /**
     * 应退金额
     */
    @ApiModelProperty(value = "应退金额", example = "-12")
    private BigDecimal dueAmount;

    /**
     * 实退金额
     */
    @ApiModelProperty(value = "实退金额", example = "-13")
    private BigDecimal actualAmount;

    /**
     * 退费课时
     */
    @ApiModelProperty(value = "退费课时", example = "2")
    private Integer refundLessonCount;

    /**
     * 退费说明
     */
    @ApiModelProperty(value = "退费说明", example = "没时间")
    private String remark;

    /**
     * 退费状态
     */
    @ApiModelProperty(value = "退费状态【1待审核 2已审核】", example = "1")
    private Integer refundRerifyState;


}
