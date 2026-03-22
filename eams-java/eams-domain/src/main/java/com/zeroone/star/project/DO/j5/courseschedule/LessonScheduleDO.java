package com.zeroone.star.project.DO.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("lesson_schedule")
public class LessonScheduleDO {
    @TableId(type = IdType.AUTO)
    private Long id;
    private Long courseId;//课程id
    private Long teacherIds;//是老师
    private Long assistantIds;//还是助教

}
