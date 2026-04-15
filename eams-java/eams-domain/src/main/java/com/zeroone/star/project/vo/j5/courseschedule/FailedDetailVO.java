package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;

/**
 * 失败详情VO
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@ApiModel(description = "失败详情VO")
@Data
public class FailedDetailVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "排课计划ID", example = "1001")
    private Long scheduleId;

    @ApiModelProperty(value = "失败原因", example = "该排课计划已生成课表")
    private String reason;

    @ApiModelProperty(value = "错误代码", example = "SCHEDULE_ALREADY_GENERATED")
    private String errorCode;
}
