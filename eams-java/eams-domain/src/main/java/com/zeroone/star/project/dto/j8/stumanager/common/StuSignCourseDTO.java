package com.zeroone.star.project.dto.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.*;
import java.math.BigDecimal;
import java.time.LocalDateTime;

@ApiModel("报名签单保存DTO")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class StuSignCourseDTO {

    @ApiModelProperty(value = "报名ID（修改必传，新增不传）")
    private Long id;

    @NotNull(message = "必须选择学生")
    @ApiModelProperty(value = "学生ID", required = true)
    private Long studentId;

    @NotNull(message = "必须选择课程")
    @ApiModelProperty(value = "课程ID", required = true)
    private Long courseId;

    @NotBlank(message = "请选择报名类型")
    @ApiModelProperty(value = "报名类型", required = true)
    private String enrollType;

    @NotNull(message = "开始日期不能为空")
    @ApiModelProperty(value = "开始日期", required = true)
    private LocalDateTime beginDate;

    @NotNull(message = "有效期至不能为空")
    @Future(message = "有效期必须是未来时间")
    @ApiModelProperty(value = "有效期至", required = true)
    private LocalDateTime expiredDate;

    @NotNull(message = "购买课时数不能为空")
    @Min(value = 1, message = "购买课时数必须大于0")
    @ApiModelProperty(value = "购买课时数", required = true)
    private Integer lessonCount;

    @NotNull(message = "课程金额不能为空")
    @DecimalMin(value = "0", message = "课程金额不能为负数")
    @ApiModelProperty(value = "课程金额", required = true)
    private BigDecimal courseAmount;

    @NotNull(message = "实收金额不能为空")
    @DecimalMin(value = "0", message = "实收金额不能为负数")
    @ApiModelProperty(value = "实收金额", required = true)
    private BigDecimal realAmount;

    @DecimalMin(value = "0", message = "优惠金额不能为负数")
    @ApiModelProperty(value = "优惠金额")
    private BigDecimal discountAmount;

    @ApiModelProperty(value = "收款经手人")
    private String counselor;

    @ApiModelProperty(value = "备注")
    private String remark;

    @ApiModelProperty(value = "财务审核通过课时数")
    private Integer verifiedLessonCount;
}