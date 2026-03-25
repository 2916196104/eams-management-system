package com.zeroone.star.project.dto.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@ApiModel("课程报名DTO")
public class MyRegistrationDTO {

    @ApiModelProperty(value = "主键ID")
    private Long id;

    @ApiModelProperty(value = "学生ID")
    private Long studentId;

    @ApiModelProperty(value = "学生名称")
    private String studentName;

    @ApiModelProperty(value = "课程ID")
    private Long courseId;

    @ApiModelProperty(value = "课程名称")
    private String courseName;

    @ApiModelProperty(value = "科目ID")
    private Long subjectId;

    @ApiModelProperty(value = "科目名称")
    private String subjectName;

    @ApiModelProperty(value = "购买课次")
    private Integer countLessonTotal;

    @ApiModelProperty(value = "合约金额")
    private BigDecimal amount;

    @ApiModelProperty(value = "实付金额")
    private BigDecimal paidAmount;

    @ApiModelProperty(value = "欠费")
    private BigDecimal arrearsAmount;

    @ApiModelProperty(value = "开始日期")
    private LocalDate startDate;

    @ApiModelProperty(value = "有效期至")
    private LocalDate expireDate;

    @ApiModelProperty(value = "退费金额")
    private BigDecimal refundAmount;

    @ApiModelProperty(value = "退课次数")
    private Integer countLessonRefund;

    @ApiModelProperty(value = "退费说明")
    private String refundRemark;

    @ApiModelProperty(value = "退费状态")
    private Integer refundState;

    @ApiModelProperty(value = "退费状态名称")
    private String refundStateName;

    @ApiModelProperty(value = "录入时间")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "组织ID")
    private Long orgId;
}
