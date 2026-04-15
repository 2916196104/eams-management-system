package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.math.BigDecimal;
import java.time.LocalDate;

@Data
@ApiModel(description = "学员课程详情VO")
public class StudentDetailVO {
    @ApiModelProperty(value = "学员ID", example = "1")
    private String studentId;

    @ApiModelProperty(value = "学员姓名", example = "sdadadsdsadd")
    private String studentName;

    @ApiModelProperty(value = "总课时数", example = "20")
    private Integer countLessonTotal;

    @ApiModelProperty(value = "已完成课时数", example = "12")
    private Integer countLessonComplet;

    @ApiModelProperty(value = "已退款课时数", example = "2")
    private Integer countLessonRefund;

    @ApiModelProperty(value = "剩余课时数", example = "6")
    private Integer remainingTimes;

    @ApiModelProperty(value = "课程开始日期", example = "2025-03-01")
    private LocalDate startDate;

    @ApiModelProperty(value = "课程过期日期", example = "2026-03-01")
    private LocalDate expireDate;

    @ApiModelProperty(value = "课程总金额", example = "2000.00")
    private BigDecimal courseAmount;

    @ApiModelProperty(value = "实付金额", example = "1800.00")
    private BigDecimal paidAmount;

    @ApiModelProperty(value = "课程名称", example = "钢琴入门课")
    private String courseName;          // 新增：课程名称

    @ApiModelProperty(value = "学习进度", example = "8/50")
    private String progress;            // 格式：已完成/总数

}