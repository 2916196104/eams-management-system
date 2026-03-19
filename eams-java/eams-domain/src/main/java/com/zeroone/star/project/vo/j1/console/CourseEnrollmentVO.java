package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

@Data
@ApiModel(value = "CourseEnrollmentVO", description = "课程报名统计视图对象")
public class CourseEnrollmentVO {

    @ApiModelProperty(value = "总记录数")
    private Long total;

    @ApiModelProperty(value = "报名列表")
    private List<CourseEnrollmentItem> list;

    @Data
    @ApiModel(value = "CourseEnrollmentItem", description = "单条报名记录")
    public static class CourseEnrollmentItem {

        @ApiModelProperty(value = "主键ID")
        private Long id;

        @ApiModelProperty(value = "学生id")
        private Long studentId;

        @ApiModelProperty(value = "课程id")
        private Long courseId;

        @ApiModelProperty(value = "科目id")
        private Long subjectId;

        @ApiModelProperty(value = "开始时间")
        private LocalDate startDate;

        @ApiModelProperty(value = "过期日期")
        private LocalDate expireDate;

        @ApiModelProperty(value = "备注")
        private String remark;

        @ApiModelProperty(value = "购买总课次")
        private Integer countLessonTotal;

        @ApiModelProperty(value = "已上课次")
        private Integer countLessonComplete;

        @ApiModelProperty(value = "退款次数")
        private Integer countLessonRefund;

        @ApiModelProperty(value = "套餐金额")
        private BigDecimal courseAmount;

        @ApiModelProperty(value = "优惠金额")
        private BigDecimal discountAmount;

        @ApiModelProperty(value = "成交/合约金额")
        private BigDecimal amount;

        @ApiModelProperty(value = "实付金额")
        private BigDecimal paidAmount;

        @ApiModelProperty(value = "是否付清 0否 1是")
        private Boolean payOff;

        @ApiModelProperty(value = "经手人")
        private Long operator;

        @ApiModelProperty(value = "创建人")
        private Long creator;

        @ApiModelProperty(value = "录入时间")
        private LocalDateTime addTime;

        @ApiModelProperty(value = "编辑人")
        private Long editor;

        @ApiModelProperty(value = "编辑时间")
        private LocalDateTime editTime;

        @ApiModelProperty(value = "删除标记")
        private Boolean deleted;

        @ApiModelProperty(value = "审核状态")
        private Integer verifyState;

        @ApiModelProperty(value = "不足时已提醒次数")
        private Integer warningTimes;

        @ApiModelProperty(value = "消课优先级")
        private Integer priority;

        @ApiModelProperty(value = "单价")
        private BigDecimal unitPrice;

        @ApiModelProperty(value = "是否来自于体验试用")
        private Boolean fromTrial;

        @ApiModelProperty(value = "报名老师所属组织ID")
        private Long orgId;

        // --- 关联查询/计算字段（非表字段） ---

        @ApiModelProperty(value = "学生名称（关联student表）")
        private String studentName;

        @ApiModelProperty(value = "课程名称（关联course表）")
        private String courseName;

        @ApiModelProperty(value = "科目名称（关联subject表）")
        private String subjectName;

        @ApiModelProperty(value = "欠费（计算字段：amount - paidAmount）")
        private BigDecimal arrearsAmount;

        @ApiModelProperty(value = "退费金额（计算字段）")
        private BigDecimal refundAmount;

        @ApiModelProperty(value = "退费说明")
        private String refundRemark;

        @ApiModelProperty(value = "退费状态")
        private Integer refundState;
    }
}
