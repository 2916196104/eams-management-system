package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalTime;

@Data
@ApiModel(value = "课次日历VO", description = "课次日历返回")
public class LessonCalendarVO {
    @ApiModelProperty(value = "ID")
    private Long id;
    @ApiModelProperty(value = "标题")
    private String title;
    @ApiModelProperty(value = "上课日期")
    private LocalDate date;
    @ApiModelProperty(value = "开始时间")
    private LocalTime startTime;
    @ApiModelProperty(value = "结束时间")
    private LocalTime endTime;
    @ApiModelProperty(value = "班级名称")
    private String className;
    @ApiModelProperty(value = "课程名称")
    private String courseName;
    @ApiModelProperty(value = "教师名称")
    private String teacherName;
    @ApiModelProperty(value = "教室名称")
    private String roomName;
}
