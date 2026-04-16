package com.zeroone.star.project.dto.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import javax.validation.constraints.NotNull;
import java.math.BigDecimal;

/**
 * <p>
 * 描述：课程选择新增数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author tsfmn
 * @version 1.0.0
 */
@Getter
@Setter
@ToString
@ApiModel("课程选择新增数据传输对象")
public class StuChooseCourseAddDTO {
    @ApiModelProperty(value = "课程ID", example = "1")
    @NotNull(message = "课程ID不能为空")
    private Long courseId;

    @ApiModelProperty(value = "课程名称", example = "Java进阶")
    @NotNull(message = "课程名称不能为空")
    private String courseName;

    @ApiModelProperty(value = "课时", example = "40")
    @NotNull(message = "课时不能为空")
    private Integer lessonCount;

    @ApiModelProperty(value = "单价", example = "100.00")
    @NotNull(message = "单价不能为空")
    private BigDecimal unitPrice;

    @ApiModelProperty(value = "总价", example = "4000.00")
    @NotNull(message = "总价不能为空")
    private BigDecimal totalPrice;

    @ApiModelProperty(value = "单位(期/次)", example = "期")
    @NotNull(message = "单位不能为空")
    private String unitName;

    @ApiModelProperty(value = "有效期月数（时长）", example = "12")
    @NotNull(message = "有效期月数不能为空")
    private Integer expireMonths;

    @ApiModelProperty(value = "课堂类型 1大课 2小班课 3一对一", example = "1")
    @NotNull(message = "课堂类型不能为空")
    private Integer lessonType;
}
