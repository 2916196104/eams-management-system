package com.zeroone.star.project.dto.j7.interaction;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.Max;
import javax.validation.constraints.Min;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

@Data
@ApiModel(value = "作业点评DTO")
public class HomeworkCommentDTO {
    @ApiModelProperty(value = "作业记录ID", required = true)
    @NotNull(message = "作业记录ID不能为空")
    private Long homeworkRecordId;

    @ApiModelProperty(value = "点评内容", required = true)
    @NotBlank(message = "点评内容不能为空")
    private String content;

    @ApiModelProperty(value = "评分 0-100", required = true)
    @NotNull(message = "评分不能为空")
    @Min(value = 0, message = "得分不能低于0")
    @Max(value = 100, message = "得分不能超过100")
    private Integer score;
}