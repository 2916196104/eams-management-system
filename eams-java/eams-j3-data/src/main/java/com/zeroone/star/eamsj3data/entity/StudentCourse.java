package com.zeroone.star.eamsj3data.entity;

import com.baomidou.mybatisplus.annotation.*;
import com.baomidou.mybatisplus.annotation.FieldFill;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@TableName("student_course")
public class StudentCourse implements Serializable {
    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.AUTO)
    @ApiModelProperty("主键ID")
    private Long id;

    @ApiModelProperty("学生ID")
    private Long studentId;

    @ApiModelProperty("课程ID")
    private Long courseId;

    @ApiModelProperty("科目ID")
    private Long subjectId;

    @ApiModelProperty("开始时间")
    private LocalDate startDate;

    @ApiModelProperty("过期日期")
    private LocalDate expireDate;

    @ApiModelProperty("备注")
    private String remark;

    @ApiModelProperty("购买总课次")
    private Integer countLessonTotal;

    @ApiModelProperty("已上课次")
    private Integer countLessonComplete;

    @ApiModelProperty("退款次数")
    private Integer countLessonRefund;

    @ApiModelProperty("套餐金额")
    private BigDecimal courseAmount;

    @ApiModelProperty("优惠金额")
    private BigDecimal discountAmount;

    @ApiModelProperty("成交/合约金额")
    private BigDecimal amount;

    @ApiModelProperty("实付金额")
    private BigDecimal paidAmount;

    @ApiModelProperty("是否付清 (0 否 1 是)")
    private Integer payOff;

    @ApiModelProperty("经手人")
    private Long operator;

    @ApiModelProperty("创建人")
    private Long creator;

    @TableField(fill = FieldFill.INSERT)
    @ApiModelProperty("录入时间")
    private LocalDateTime addTime;

    @ApiModelProperty("编辑人")
    private Long editor;

    @TableField(fill = FieldFill.INSERT_UPDATE)
    @ApiModelProperty("编辑时间")
    private LocalDateTime editTime;

    @TableLogic
    @ApiModelProperty("删除标记 (0 正常 1 已删除)")
    private Integer deleted;

    @ApiModelProperty("审核状态")
    private Integer verifyState;

    @ApiModelProperty("不足时已提醒次数")
    private Integer warningTimes;

    @ApiModelProperty("消课优先级")
    private Integer priority;

    @ApiModelProperty("单价")
    private BigDecimal unitPrice;

    @ApiModelProperty("是否来自于体验课")
    private Integer fromTrial;

    @ApiModelProperty("报名老师所属机构")
    private Long orgId;
}
