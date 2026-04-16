package com.zeroone.star.project.vo.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalTime;

@ApiModel("课表")
@Data
public class ClassScheduleVO {
    @ApiModelProperty(value = "序号", example = "2")
    private Long id;
    @ApiModelProperty(value = "日期", example = "2026-01-02")
    private LocalDate date;
    @ApiModelProperty(value = "开始时间", example = "10:00", dataType = "java.lang.String")
    private LocalTime beginTime;
    @ApiModelProperty(value = "结束时间", example = "11:30", dataType = "java.lang.String")
    private LocalTime endTime;
    @ApiModelProperty(value = "课程标题", example = "xxxx")
    private String title;
    @ApiModelProperty(value = "教师姓名", example = "xxx")
    private String teacher;
    @ApiModelProperty(value = "班级", example = "1班")
    private String className;
    @ApiModelProperty(value = "教室", example = "xxx")
    private String classroom;
    @ApiModelProperty(value = "听课方式", example = "xxxx")
    private Integer listenType;
    @ApiModelProperty(value = "实扣课次", example = "5")
    private Integer decLessonCount;
    @ApiModelProperty(value = "签到状态", example = "1")
    private Integer signState;
}
