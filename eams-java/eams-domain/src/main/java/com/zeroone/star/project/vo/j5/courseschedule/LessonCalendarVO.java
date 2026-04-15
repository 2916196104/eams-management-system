package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.List;

@Data
public class LessonCalendarVO {

    private Long id;                // 课表ID

    @ApiModelProperty("标题")
    private String title;
    @ApiModelProperty("课程名称")
    private String courseName;      // 课程名称
    @ApiModelProperty("老师名称")
    private String teacherName;     // 老师名称
    @ApiModelProperty("学生id列表")
    private List<String> studentIdList;
    @ApiModelProperty("学生名称列表")
    private List<String> studentNameList;
    @ApiModelProperty("班级类型")
    private String classType;

    private LocalDate Date;   // 上课日期
    private LocalTime startTime;    // 开始时间
    private LocalTime endTime;      // 结束时间

    @ApiModelProperty("班级名称")
    private String className;       // 班级名称

    @ApiModelProperty("教室名称")
    private String classroomName;   // 教室名称


    @ApiModelProperty("课程状态")
    private String courseStatus;     // 课程状态

    @ApiModelProperty(value = "课表日历类型", notes = "true-学生课表, false-老师课表")
    private Boolean courseCalendarType;


}
