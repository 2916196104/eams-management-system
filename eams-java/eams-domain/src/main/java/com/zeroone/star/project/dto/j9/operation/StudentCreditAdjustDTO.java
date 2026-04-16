package com.zeroone.star.project.dto.j9.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;

/**
 * 调整学生积分参数 DTO
 */
@Data
@ApiModel(description = "调整学生积分参数")
public class StudentCreditAdjustDTO {

    @NotNull(message = "学生ID不能为空")
    @ApiModelProperty(value = "学生ID（对应前端「选择学生」）", required = true, example = "5001")
    private Long studentId;

    @NotNull(message = "调整积分数不能为空")
    @ApiModelProperty(value = "调整积分数（扣减写负数，增加写正数）", required = true, example = "-200")
    private Integer adjustCredit;

    @ApiModelProperty(value = "调整原因（可选）", example = "管理员手动调整积分")
    private String adjustReason;
}