package com.zeroone.star.project.dto.j5.courseplan;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalTime;

/**
 * 上课时间设置DTO
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@Data
@ApiModel(description = "上课时间设置DTO")
public class TimeSettingDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "星期（1-7，多个用逗号分隔）", example = "1,3,5")
    private String weeks;

    @ApiModelProperty(value = "开始时间", example = "09:00:00")
    private LocalTime startTime;

    @ApiModelProperty(value = "结束时间", example = "10:30:00")
    private LocalTime endTime;

    @ApiModelProperty(value = "教室ID", example = "5001")
    private Long roomId;
}
