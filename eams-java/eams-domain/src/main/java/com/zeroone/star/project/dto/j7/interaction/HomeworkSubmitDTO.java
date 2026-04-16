package com.zeroone.star.project.dto.j7.interaction;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

@Data
@ApiModel(value = "学生提交作业DTO")
public class HomeworkSubmitDTO {
    @ApiModelProperty(value = "教师发布的作业ID", required = true)
    @NotNull(message = "作业ID不能为空")
    private Long homeworkId;

    @ApiModelProperty(value = "学生提交的作业内容", required = true)
    @NotBlank(message = "作业内容不能为空")
    private String content;
}