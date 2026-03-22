package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

@Data
@ApiModel(value = "CourseEnrollmentVO", description = "课程报名列表视图对象")
public class MyRegistrationVO {

    @ApiModelProperty(value = "总记录数")
    private Long total;

    @ApiModelProperty(value = "报名列表")
    private List<CourseEnrollmentItem> list;

    @Data
    @ApiModel(value = "CourseEnrollmentItem", description = "单条报名记录")
    public static class CourseEnrollmentItem {

        @ApiModelProperty(value = "主键ID")
        private Long id;

        @ApiModelProperty(value = "添加时间")
        private LocalDateTime addTime;

        @ApiModelProperty(value = "学生")
        private String studentName;

        @ApiModelProperty(value = "课程")
        private String courseName;

        @ApiModelProperty(value = "科目")
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
    }
}
