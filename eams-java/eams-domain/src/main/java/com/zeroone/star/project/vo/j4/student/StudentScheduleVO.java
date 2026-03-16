package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalTime;
import java.util.Date;

@Data
@ApiModel("课表")
public class StudentScheduleVO {
    @ApiModelProperty(value = "日期", example = "2026-09-09")
    LocalDate date;

    @ApiModelProperty(value = "开始时间", example = "8:00")
    LocalTime startTime;

    @ApiModelProperty(value = "结束时间", example = "10:00")
    LocalTime endTime;

    @ApiModelProperty(value = "课程", example = "足球")
    String courseName;

    @ApiModelProperty(value = "教师", example = "张三")
    String teacherName;

    @ApiModelProperty(value = "班级", example = "足球特长班")
    String className;

    @ApiModelProperty(value = "教室", example = "101")
    String classroomName;

    @ApiModelProperty(value = "听课方式", example = "面授")
    String teachType;

    @ApiModelProperty(value = "实扣课时", example = "2.0")
    BigDecimal decLessonCount;

    @ApiModelProperty(value = "签到状态", example = "未签到")
    String signState;
}
