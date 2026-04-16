package com.zeroone.star.project.dto.j7.interaction;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;
import java.util.List;

@Data
@ApiModel(value = "作业删除DTO")
public class HomeworkDeleteDTO {
    @ApiModelProperty(value = "作业ID列表", required = true)
    @NotNull(message = "作业ID列表不能为空")
    private List<Long> ids;
}