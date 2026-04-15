package com.zeroone.star.project.dto.j5.courseplan;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotEmpty;
import java.io.Serializable;
import java.util.List;

/**
 * 删除已生成课表请求DTO
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@Data
@ApiModel(value = "删除已生成课表请求DTO", description = "用于删除已生成课表的请求参数")
public class DeleteLessonDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "要删除课表的排课计划ID数组", example = "[1001, 1002, 1003]", required = true)
    @NotEmpty(message = "排课计划ID数组不能为空")
    private List<Long> scheduleIds;

    @ApiModelProperty(value = "是否强制删除（包括已签到的课次）", example = "false", notes = "默认值为false")
    private Boolean forceDelete = false;

    @ApiModelProperty(value = "删除原因，用于操作日志记录", example = "排课计划调整")
    private String deleteReason;
}
