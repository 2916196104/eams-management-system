package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.time.LocalTime;

@Data
@ApiModel(description = "排课详细设置项")
public class LessonScheduleSettingDTO {
    // ✅ 方案：组合拳
    // 1. @NotBlank: 后端真实校验，没传就报错
    // 2. @ApiModelProperty: 前端文档显示必填，并给出示例
    @NotBlank(message = "星期几不能为空")
    @ApiModelProperty(value = "周几 (1-7)", required = true, example = "1")
    private String weeks;

    @NotNull(message = "开始时间不能为空")
    @ApiModelProperty(value = "开始时间", required = true, example = "08:00")
    private LocalTime startTime;

    @NotNull(message = "结束时间不能为空")
    @ApiModelProperty(value = "结束时间", required = true, example = "09:30")
    private LocalTime endTime;

    @NotNull(message = "教室 ID 不能为空")
    @ApiModelProperty(value = "教室 ID", example = "101")
    private Long roomId;
}
