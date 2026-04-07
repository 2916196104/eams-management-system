package com.zeroone.star.project.DO.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("lesson_teacher")
public class LessonTeacherDo {
    @TableId(type = IdType.AUTO)
    private Long id;
    private Long lessonId;
    private Long teacherId;
    private Integer typeNum;
}