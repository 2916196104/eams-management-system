package com.zeroone.star.project.dto.j5.coursrschedule;

import lombok.Data;

import java.time.LocalDate;
import java.time.LocalTime;

@Data
public class LessonDTO {

        private Long id;                // 课表ID
        private LocalDate Date;   // 上课日期
        private LocalTime startTime;    // 开始时间
        private LocalTime endTime;      // 结束时间


        private String className;       // 班级名称
        private String courseName;      // 课程名称
        private String teacherName;     // 老师名称
        private String subjectName;     // 科目名称
        private String classroomName;   // 教室名称

}
