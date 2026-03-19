package com.zeroone.star.project.do_.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalTime;

@Data
@TableName("lesson")
public class LessonDo {
    @TableId(type = IdType.AUTO)
    private Long id;                // 主键ID
    private Long classId;           // 班级ID
    private Long courseId;          // 课程ID
    private Long teacherId;         // 老师ID
    private Long subjectId;         // 科目ID
    private Long classroomId;       // 教室ID
    private LocalDate date;   // 上课日期
    private LocalTime startTime;    // 开始时间
    private LocalTime endTime;      // 结束时间

}
