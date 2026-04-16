package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

/**
 * 描述：章节数据传输对象
 */
@Data
@ApiModel("章节数据")
public class ChapterDTO {
    @ApiModelProperty(value = "章节id, 如果是修改数据必须传，新增不传", example = "2008418408985583617")
    private Long id;

    @NotNull(message = "课程ID不能为空")
    @ApiModelProperty(value = "所属课程ID", example = "1001", required = true)
    private Long courseId;

    @NotBlank(message = "章节标题不能为空")
    @ApiModelProperty(value = "章节标题", example = "第一章 基础介绍", required = true)
    private String title;

    @NotNull(message = "计划课时不能为空")
    @ApiModelProperty(value = "计划课时", example = "10", required = true)
    private Integer plannedHours;
}