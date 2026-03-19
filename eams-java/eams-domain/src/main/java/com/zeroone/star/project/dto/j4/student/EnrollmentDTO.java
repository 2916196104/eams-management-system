package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

//EnrollmentDTO: 报名操作封装（课程、金额、初始课时）。
@Data
@ApiModel("报名记录DTO")
public class EnrollmentDTO {

    @ApiModelProperty(value = "报名ID")
    private Long id;

    @ApiModelProperty(value = "学生姓名")
    private String studentName;

    @ApiModelProperty(value = "课程名称")
    private String courseName;

    @ApiModelProperty(value = "科目名称")
    private String subjectName;

    @ApiModelProperty(value = "报名时间")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "报名金额")
    private BigDecimal amount;

    @ApiModelProperty(value = "购买总课次")
    private Integer countLessonTotal;

    @ApiModelProperty(value = "已上课次")
    private Integer countLessonComplete;

    @ApiModelProperty(value = "剩余课次")
    private Integer remainingLessons;

    @ApiModelProperty(value = "审核状态")
    private Integer verifyState;

    @ApiModelProperty(value = "经手人")
    private String operatorName;
}
