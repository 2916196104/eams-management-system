package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class CourseScheduleSettingVO {
    @ApiModelProperty( value = "课程表编号", example = "1")
    private String scheduleId;

    @ApiModelProperty( value = "星期几上课", example = "星期五", required = true)
    private String weeks;
    @ApiModelProperty( value = "上课开始时间", example = "2023-01-01 09:00:00", required = true )
    private String startTime;
    @ApiModelProperty( value = "上课结束时间", example = "2023-01-01 10:00:00", required = true)
    private String endTime;
    @ApiModelProperty( value = "教室号", example = "1")
    private Integer roomId;

}
