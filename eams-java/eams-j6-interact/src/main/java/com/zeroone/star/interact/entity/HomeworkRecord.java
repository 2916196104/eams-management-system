package com.zeroone.star.interact.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 作业提交记录实体
 */
@Data
@TableName("homework_record")
public class HomeworkRecord {

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    @TableField("homework_id")
    private Long homeworkId;

    @TableField("student_id")
    private Long studentId;

    @TableField("add_time")
    private LocalDateTime addTime;

    @TableField("content")
    private String content;

    @TableField("score")
    private Integer score;

    @TableField("comment")
    private String comment;

    @TableField("comment_time")
    private LocalDateTime commentTime;

    @TableField("comment_teacher")
    private Long commentTeacher;

    @TableField("images")
    private String images;
}
