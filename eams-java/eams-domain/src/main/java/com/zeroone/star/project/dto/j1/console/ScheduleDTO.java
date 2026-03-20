package com.zeroone.star.project.dto.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@ApiModel("课表日历DTO")
public class ScheduleDTO {

    @ApiModelProperty(value = "主键ID")
    private Long id;

    @ApiModelProperty(value = "班级ID")
    private Long classId;

    @ApiModelProperty(value = "班级名称")
    private String className;

    @ApiModelProperty(value = "课程ID")
    private Long courseId;

    @ApiModelProperty(value = "课程名称")
    private String courseName;

    @ApiModelProperty(value = "教师ID串")
    private String teacherIds;

    @ApiModelProperty(value = "上课老师")
    private String teacherName;

    @ApiModelProperty(value = "助教ID串")
    private String assistantIds;

    @ApiModelProperty(value = "助教")
    private String assistantName;

    @ApiModelProperty(value = "开始日期")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束日期")
    private LocalDate endDate;

    @ApiModelProperty(value = "上课时间")
    private LocalDateTime startTime;

    @ApiModelProperty(value = "类型")
    private String typeName;

    @ApiModelProperty(value = "教室")
    private String classroom;

    @ApiModelProperty(value = "可预约")
    private Integer reserveCount;

    @ApiModelProperty(value = "学生数")
    private Integer studentCount;

    @ApiModelProperty(value = "签到数")
    private Integer signCount;

    @ApiModelProperty(value = "到课率")
    private BigDecimal attendanceRate;

    @ApiModelProperty(value = "消课基数")
    private Integer lessonBase;

    @ApiModelProperty(value = "已消课数")
    private Integer lessonUsed;

    @ApiModelProperty(value = "上课情况")
    private String lessonStatus;

    @ApiModelProperty(value = "状态值")
    private Boolean state;

    @ApiModelProperty(value = "状态")
    private String stateName;
}
