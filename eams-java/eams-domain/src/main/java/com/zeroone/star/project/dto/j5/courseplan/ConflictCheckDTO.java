package com.zeroone.star.project.dto.j5.courseplan;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.util.List;

/**
 * 冲突检查请求DTO
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@Data
@ApiModel(value = "冲突检查请求DTO")
public class ConflictCheckDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "排课计划ID数组，与scheduleInfo二选一", example = "[1001, 1002]")
    private List<Long> scheduleIds;

    @ApiModelProperty(value = "排课信息对象数组，用于预检查")
    private List<ScheduleInfoDTO> scheduleInfo;

    @ApiModelProperty(value = "检查类型：teacher(教师)/room(教室)/all(全部)", example = "all", allowableValues = "teacher,room,all")
    private String checkType = "all";

    @ApiModelProperty(value = "是否忽略已生成课表的计划", example = "true")
    private Boolean ignoreGenerated = true;

}
