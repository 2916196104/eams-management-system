package com.zeroone.star.project.dto.j5.coursrschedule;

import lombok.Data;

@Data
public class LessonListDTO {
    private Long id;
    // 格式化后的时间（前端直接展示）
    private String lessonTime;
    // 多表关联字段
    private String courseName;
    private String className;
    private String teacherName;
    private String classroomName;
    private Integer lessonType;//课堂类型
    private Integer bookable; //是否可以预约
    private Integer signState;//签到结果

}
