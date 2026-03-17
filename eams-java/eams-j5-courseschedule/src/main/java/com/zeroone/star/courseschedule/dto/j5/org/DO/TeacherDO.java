package com.zeroone.star.courseschedule.dto.j5.org.DO;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("lesson_teacher")
public class TeacherDO {
    @TableId(type = IdType.AUTO)
    private Long id;
    private Long lessonId;
}
