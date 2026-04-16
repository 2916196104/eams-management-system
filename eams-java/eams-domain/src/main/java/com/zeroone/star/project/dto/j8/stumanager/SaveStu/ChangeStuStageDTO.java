package com.zeroone.star.project.dto.j8.stumanager.SaveStu;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;

@Data
@ApiModel("学员状态DTO")
public class ChangeStuStageDTO {

    @NotNull(message = "学员ID不能为空")
    @ApiModelProperty(value = "学员主键ID", required = true, example = "1")
    private Long id;

    @ApiModelProperty(value = "阶段状态 0-意向学员（默认0）", example = "0")
    private Integer stage = 0;
}
