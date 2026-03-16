package com.zeroone.star.project.dto.j3.course;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
public class CourseStatusDTO {
    @ApiModelProperty(value = "需要修改的课程的id", required = true)
    private List<Long> ids;
    @ApiModelProperty(value = "需要修改的目标状态", required = true, example = "1")
    private Integer status; // 目标状态
}