package com.zeroone.star.j7.interaction.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * homework_record 表的实体类
 * </p>
 * @author lvincent
 * @since 2026-03-16
 */
@Data
@TableName("homework_record")
public class HomeworkRecord implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long homeworkId;

    private Long studentId;

    private LocalDateTime addTime;

    private String content;

    private Integer score;

    private String comment;

    private LocalDateTime commentTime;

    private Long commentTeacher;

    private String images;

    private Integer status;

    private Boolean deleted;

    private Long creator;

    private Long commenter;

    private LocalDateTime createTime;
}
