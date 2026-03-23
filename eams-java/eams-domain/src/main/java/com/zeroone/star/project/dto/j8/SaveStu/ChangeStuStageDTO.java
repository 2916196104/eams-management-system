package com.zeroone.star.project.dto.j8.SaveStu;

import io.swagger.annotations.ApiModelProperty;

import javax.validation.constraints.NotNull;

public class ChangeStuStageDTO {

    @NotNull(message = "学员ID不能为空") // 修正：ID是Long类型，不能用@NotBlank（仅适用于字符串）
    @ApiModelProperty(value = "学员主键ID", required = true, example = "1")
    private Long id;

    @ApiModelProperty(value = "阶段状态 0-意向学员（默认0）", example = "0")
    private Integer stage = 0;
}
