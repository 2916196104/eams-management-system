package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

/**
 * <p>
 * 描述：报名记录视图对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 康康舞曲
 * @version 1.0.0
 */
@ApiModel("报名记录视图对象")
@Data
public class MyEnrollmentVO {

    @ApiModelProperty(value = "报名记录ID", example = "1001")
    private Long id;

    @ApiModelProperty(value = "报名时间", example = "2024-03-15 10:30:00")
    private String enrollmentTime;

    @ApiModelProperty(value = "学生姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "课程名称", example = "Java高级编程")
    private String courseName;

    @ApiModelProperty(value = "科目名称", example = "编程")
    private String subjectName;

    @ApiModelProperty(value = "购买课次", example = "24")
    private Integer purchaseLessonCount;

    @ApiModelProperty(value = "单价", example = "150.00")
    private BigDecimal unitPrice;

    @ApiModelProperty(value = "合约金额", example = "3600.00")
    private BigDecimal contractAmount;

    @ApiModelProperty(value = "实付金额", example = "3200.00")
    private BigDecimal paidAmount;

    @ApiModelProperty(value = "欠费", example = "400.00")
    private BigDecimal arrearsAmount;

    @ApiModelProperty(value = "开始日期", example = "2024-03-01")
    private String startDate;

    @ApiModelProperty(value = "有效期至", example = "2025-03-01")
    private String expireDate;

    @ApiModelProperty(value = "退费总金额", example = "300.00")
    private BigDecimal refundTotalAmount;

    @ApiModelProperty(value = "退费总次数", example = "1")
    private Integer refundTotalCount;

    @ApiModelProperty(value = "退费说明", example = "因课程调整退费")
    private String refundRemark;
}
