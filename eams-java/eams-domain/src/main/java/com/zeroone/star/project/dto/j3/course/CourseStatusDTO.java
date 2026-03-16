package com.zeroone.star.project.dto.j3.course;

import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.Max;
import javax.validation.constraints.Min;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Pattern;
import java.util.List;

@Data
public class CourseStatusDTO {
    @ApiModelProperty(value = "课程ID列表", example = "[1, 2, 3]", required = true)
    @NotBlank(message = "课程选择不能为空")
    private List<Long> ids;
    @ApiModelProperty(value = "目标状态 (1:启用, 0:禁用)", example = "1", required = true)
    @Min(value = 0, message = "目标状态只有1或0")
    @Max(value = 1, message = "目标状态只有1或0")
    private Integer status;
}