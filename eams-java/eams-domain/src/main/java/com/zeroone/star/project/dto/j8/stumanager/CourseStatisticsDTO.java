package com.zeroone.star.project.dto.j8.stumanager;

import lombok.Data;
/**
 * 课程统计DTO：封装课程统计的返回数据
 */
@Data // 用lombok简化get/set，若无lombok可手动写

public class CourseStatisticsDTO {
    private String courseName; //课程名称
    private String courseCode; //课程代码
    private String courseType;//课程类型
    private String courseTime;//课程时间
    private String studentName;//学生姓名
    private String studentCode;//学生学号
    private String studentType;//学生学院
    private String teacherName;//教师姓名
    private String teacherCode;//教师代码

}
