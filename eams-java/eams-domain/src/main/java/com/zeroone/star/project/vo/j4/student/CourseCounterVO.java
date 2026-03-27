package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;

@ApiModel("返回课表统计")
@Data
public class CourseCounterVO {
    @ApiModelProperty(value = "课程名", example = "足球")
    String courseName;

    @ApiModelProperty(value = "科目名", example = "体育")
    String subjectName;

    @ApiModelProperty(value = "购买课次", example = "12")
    int totalCount;

    @ApiModelProperty(value = "已上课次", example = "2")
    int countLessonComplete;

    @ApiModelProperty(value = "剩余课次", example = "10")
    int remainingCount;

    @ApiModelProperty(value = "单价", example = "300")
    BigDecimal unitPrice;

    @ApiModelProperty(value = "剩余金额", example = "3000")
    BigDecimal remainingAmount;

    @ApiModelProperty(value = "到期日期", example = "2026-04-16")
    LocalDate expireDate;

    @ApiModelProperty(value = "消课优先级", example = "1")
    int priority;
}
