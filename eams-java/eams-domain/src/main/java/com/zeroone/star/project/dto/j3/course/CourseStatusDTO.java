package com.zeroone.star.project.dto.j3.course;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
public class CourseStatusDTO {
    @ApiModelProperty(value = "课程ID列表", example = "[1, 2, 3]", required = true)
    private List<Long> ids;
    @ApiModelProperty(value = "目标状态 (1:启用, 0:禁用)", example = "1", required = true)
    private Integer status;
}