package com.zeroone.star.project.dto.j5.courseplan;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDate;
import java.util.List;

/**
 * 排课信息DTO（用于冲突预检查）
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@Data
@ApiModel(value = "ScheduleInfoDTO", description = "排课信息DTO")
public class ScheduleInfoDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "班级ID", example = "2001", required = true)
    private Long classId;

    @ApiModelProperty(value = "课程ID", example = "3001", required = true)
    private Long courseId;

    @ApiModelProperty(value = "教师ID列表", example = "[101, 102]", required = true)
    private List<Long> teacherIds;

    @ApiModelProperty(value = "助教ID列表", example = "[201]")
    private List<Long> assistantIds;

    @ApiModelProperty(value = "开始日期", example = "2026-03-20", required = true)
    private LocalDate startDate;

    @ApiModelProperty(value = "结束日期", example = "2026-06-30", required = true)
    private LocalDate endDate;

    @ApiModelProperty(value = "上课时间设置列表", required = true)
    private List<TimeSettingDTO> timeSettings;
}
