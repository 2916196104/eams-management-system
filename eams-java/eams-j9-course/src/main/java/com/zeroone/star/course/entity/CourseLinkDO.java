package com.zeroone.star.course.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;

/**
 * 课程关联实体（无逻辑删除，物理删除）
 * @author yangxiao
 */
@Getter
@Setter
@TableName("course_link")
public class CourseLinkDO implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long courseId;

    private Long linkedId;
}
