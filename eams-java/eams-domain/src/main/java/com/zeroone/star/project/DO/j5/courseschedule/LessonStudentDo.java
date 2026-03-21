package com.zeroone.star.project.DO.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("lesson_schedule")
public class LessonStudentDo {
    @TableId(type = IdType.AUTO)
    private Long id;
    private Long lessonId;//课程id
    private Long studentId;//学生id
    private Integer signState;//签到结果
}
