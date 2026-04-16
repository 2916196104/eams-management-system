package com.zeroone.star.project.dto.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import javax.validation.constraints.*;
import java.math.BigDecimal;
import java.time.LocalDate;

/**
 * <p>
 * 描述：报名签单新增数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author tsfmn
 * @version 1.0.0
 */
@Getter
@Setter
@ToString
@ApiModel("报名签单新增数据传输对象")
public class StuSignCourseAddDTO {
    @NotNull(message = "必须选择学生")
    @ApiModelProperty(value = "学生ID", required = true, example = "1")
    private Long studentId;

    @NotNull(message = "必须选择课程")
    @ApiModelProperty(value = "课程ID", required = true, example = "1")
    private Long courseId;

    @ApiModelProperty(value = "收款经手人ID", example = "1")
    private Long operator;

    @NotNull(message = "必须选择科目")
    @ApiModelProperty(value = "科目ID", required = true, example = "1")
    private Long subjectId;

    @NotBlank(message = "请选择报名类型")
    @ApiModelProperty(value = "报名类型", required = true, example = "新签还是续签")
    private String enrollType;

    @NotNull(message = "开始日期不能为空")
    @ApiModelProperty(value = "开始日期", required = true, example = "2024-01-01")
    private LocalDate startDate;

    @NotNull(message = "有效期至不能为空")
    @ApiModelProperty(value = "有效期至", required = true, example = "2026-12-31")
    private LocalDate expireDate;

    @NotNull(message = "购买课时数不能为空")
    @Min(value = 1, message = "购买课时数必须大于0")
    @ApiModelProperty(value = "购买课时数", required = true, example = "40")
    private Integer countLessonTotal;

    @NotNull(message = "课程金额不能为空")
    @DecimalMin(value = "0", message = "课程金额不能为负数")
    @ApiModelProperty(value = "课程金额", required = true, example = "4000.00")
    private BigDecimal courseAmount;

    @NotNull(message = "实收金额不能为空")
    @DecimalMin(value = "0", message = "实收金额不能为负数")
    @ApiModelProperty(value = "实收金额", required = true, example = "4000.00")
    private BigDecimal paidAmount;

    @DecimalMin(value = "-999999.99", message = "优惠金额不能小于-999999.99")
    @ApiModelProperty(value = "优惠金额", example = "0.00")
    private BigDecimal discountAmount;

    @ApiModelProperty(value = "备注", example = "无")
    private String remark;
}