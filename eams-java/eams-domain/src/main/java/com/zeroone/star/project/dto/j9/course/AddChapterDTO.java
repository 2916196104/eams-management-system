package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

/**
 * <p>
 * 描述：添加章节数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Data
@ApiModel("添加章节数据传输对象")
public class AddChapterDTO {
    @ApiModelProperty(value = "章节名称", required = true, example = "第一章")
    @NotBlank(message = "章节名称不能为空")
    private String name;

    @ApiModelProperty(value = "课程ID", required = true, example = "1")
    @NotNull(message = "课程ID不能为空")
    private Long courseId;

    @ApiModelProperty(value = "排序", example = "1")
    private Integer sort;

    @ApiModelProperty(value = "描述", example = "这是第一章的内容")
    private String description;

    @ApiModelProperty(value = "计划课时数", required = true, example = "10")
    @NotNull(message = "计划课时数不能为空")
    private Integer lessonCount;
}