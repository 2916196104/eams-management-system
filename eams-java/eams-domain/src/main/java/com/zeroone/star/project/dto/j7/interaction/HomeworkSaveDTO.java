package com.zeroone.star.project.dto.j7.interaction;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

@Data
@ApiModel(value = "作业保存DTO")
public class HomeworkSaveDTO {
    @ApiModelProperty(value = "作业ID（修改时必填）")
    private Long id;

    @ApiModelProperty(value = "班级ID", required = true)
    @NotNull(message = "班级ID不能为空")
    private Long classId;

    @ApiModelProperty(value = "作业标题", required = true)
    @NotBlank(message = "作业标题不能为空")
    private String title;

    @ApiModelProperty(value = "作业内容", required = true)
    @NotBlank(message = "作业内容不能为空")
    private String content;
}