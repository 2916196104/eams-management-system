package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.List;

@Data
@ApiModel(value = "ScheduleVO", description = "课表日历视图对象")
public class TimetableCalendarVO {

    @ApiModelProperty(value = "总记录数")
    private Long total;

    @ApiModelProperty(value = "课表列表")
    private List<ScheduleItem> list;

    @Data
    @ApiModel(value = "ScheduleItem", description = "单条课表记录")
    public static class ScheduleItem {

        @ApiModelProperty(value = "主键ID")
        private Long id;

        @ApiModelProperty(value = "上课时间")
        private LocalDateTime startTime;

        @ApiModelProperty(value = "课程")
        private String courseName;

        @ApiModelProperty(value = "班级名称")
        private String className;

        @ApiModelProperty(value = "上课老师")
        private String teacherName;

        @ApiModelProperty(value = "类型")
        private String typeName;

        @ApiModelProperty(value = "助教")
        private String assistantName;

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

        @ApiModelProperty(value = "状态")
        private String stateName;
    }
}
