package com.zeroone.star.j5.courseplan.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.io.Serializable;
import java.math.BigDecimal;

/**
 * 课时老师关联表
 */
@Data
@TableName("lesson_teacher")
public class LessonTeacher implements Serializable {
    private static final long serialVersionUID = 1L;

    @TableId(type = IdType.AUTO)
    private Long id;
    private Long lessonId;
    private Long teacherId;
    private BigDecimal commission;
    private Integer typeNum; // 1上课老师 2助教
}