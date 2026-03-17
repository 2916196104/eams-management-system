package com.zeroone.star.project.dto.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

/**
 * 调整积分参数
 */
@Data
@ApiModel("调整积分参数")
public class AdjustPointsDTO {
    @NotNull(message = "学员ID不能为空")
    @ApiModelProperty(value = "学员ID", example = "1", required = true)
    private Long studentId;

    @NotNull(message = "调整积分不能为空")
    @ApiModelProperty(value = "调整积分，正数为增加，负数为扣减", example = "10", required = true)
    private Integer changeCredit;

    @NotBlank(message = "调整原因不能为空")
    @ApiModelProperty(value = "调整原因", example = "活动奖励", required = true)
    private String remark;
}
