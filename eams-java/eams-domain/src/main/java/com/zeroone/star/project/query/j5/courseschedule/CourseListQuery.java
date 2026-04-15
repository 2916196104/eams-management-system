package com.zeroone.star.project.query.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;

public class CourseListQuery {
    @ApiModelProperty(value = "周期",required = false,example = "本周")
    private Integer cycle;

    @ApiModelProperty(value = "班级名",required = false,example = "计算机四班")
    private String className;

    @ApiModelProperty(value = "课程名字",required = false,example = "java")
    private String courseName;

    @ApiModelProperty(value = "老师姓名",required = false,example = "张三")
    private String teacherName;

    @ApiModelProperty(value = "学生姓名",required = false,example = "李四")
    private String studentName;
}
