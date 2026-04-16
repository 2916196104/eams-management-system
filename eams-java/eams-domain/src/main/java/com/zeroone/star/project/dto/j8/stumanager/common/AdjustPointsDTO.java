package com.zeroone.star.project.dto.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

/**
 * Adjust points request.
 */
@Data
@ApiModel("Adjust points request")
public class AdjustPointsDTO {
    @NotNull(message = "studentId cannot be null")
    @ApiModelProperty(value = "Student ID", example = "1", required = true)
    private Long studentId;

    @NotNull(message = "changeCredit cannot be null")
    @ApiModelProperty(value = "Points delta, positive to add and negative to deduct", example = "10", required = true)
    private Integer changeCredit;

    @NotBlank(message = "remark cannot be blank")
    @ApiModelProperty(value = "Adjustment reason", example = "activity reward", required = true)
    private String remark;
}
