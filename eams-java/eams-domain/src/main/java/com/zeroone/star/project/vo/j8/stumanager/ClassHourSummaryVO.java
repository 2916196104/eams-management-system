package com.zeroone.star.project.vo.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@Data
@ApiModel(value = "ClassHourSummaryVO", description = "获取汇总列表")
public class ClassHourSummaryVO{

    @ApiModelProperty(value = "学员姓名", example = "小王")
    private String studentName;

    @ApiModelProperty(value = "课程名称", example = "S18的课程")
    private String courseName;

    @ApiModelProperty(value = "上课记录", example = "上14 假0 旷0 补0")
    private String attendanceRecord;

    @ApiModelProperty(value = "总课时", example = "144")
    private Integer totalLessonHours;
}