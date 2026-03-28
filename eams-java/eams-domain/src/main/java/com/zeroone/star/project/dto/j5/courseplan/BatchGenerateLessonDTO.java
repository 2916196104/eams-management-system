package com.zeroone.star.project.dto.j5.courseplan;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotEmpty;
import java.io.Serializable;
import java.util.List;

/**
 * 批量生成课表请求DTO
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@Data
@ApiModel(value = "批量生成课表请求DTO", description = "批量生成课表请求DTO")
public class BatchGenerateLessonDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "排课计划ID数组，为空则处理所有未生成课表的计划", example = "[1001, 1002, 1003]")
    private List<Long> scheduleIds;

    @ApiModelProperty(value = "是否排除节假日", example = "true", notes = "默认值：true")
    private Boolean excludeHoliday = true;

    @ApiModelProperty(value = "是否覆盖已生成的课表", example = "false", notes = "默认值：false")
    private Boolean overwrite = false;
}
