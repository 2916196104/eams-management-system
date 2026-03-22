package com.zeroone.star.project.query.j5.courseschedule;

import com.zeroone.star.project.query.PageQuery;
import lombok.Data;

import java.time.LocalDate;

@Data
public class CourseQuery extends PageQuery {
    private String className;      // 班级名称
    private String courseName;     // 课程名称
    private String teacherName;    // 老师名称
    private String subjectName;    // 科目名称
    private String classroomName;  // 教室名称

    // 视图参数
    private LocalDate startDate;   // 视图起始日期
    private LocalDate endDate;     // 视图结束日期
    private Integer viewType;      // 1-月视图 2-周视图 3-日视图
    private String period;        // 周期：本周/本月/自定义（对应下拉框）
}
