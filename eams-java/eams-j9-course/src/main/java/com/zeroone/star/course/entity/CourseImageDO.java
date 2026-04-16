package com.zeroone.star.course.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * 课程图片实体
 * @author yangxiao
 */
@Getter
@Setter
@TableName("course_image")
public class CourseImageDO implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long courseId;

    private String imageUrl;

    private Long creator;

    private Long editor;

    private LocalDateTime addTime;

    private LocalDateTime editTime;

    @TableLogic
    private Integer deleted;
}
