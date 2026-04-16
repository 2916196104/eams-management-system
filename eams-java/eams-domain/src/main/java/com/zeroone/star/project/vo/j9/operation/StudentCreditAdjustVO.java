package com.zeroone.star.project.vo.j9.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 调整积分结果 VO（仅返回操作状态）
 */
@Data
@ApiModel(description = "调整积分结果")
public class StudentCreditAdjustVO {

    @ApiModelProperty(value = "是否调整成功", example = "true")
    private Boolean success;

    @ApiModelProperty(value = "调整后的学生剩余积分", example = "800")
    private Integer currentCredit;
}