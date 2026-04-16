package com.zeroone.star.project.dataobject.j6.interact;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 作业提交记录 数据对象
 * </p>
 *
 * @description 对应数据库表 homework_record，用于互动模块-作业提交记录功能
 */
@Data
@TableName("homework_record")
public class HomeworkRecordDO {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 所属作业ID
     */
    @TableField("homework_id")
    private Long homeworkId;

    /**
     * 学生ID
     */
    @TableField("student_id")
    private Long studentId;

    /**
     * 提交时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 作业内容
     */
    @TableField("content")
    private String content;

    /**
     * 点评分数
     */
    @TableField("score")
    private Integer score;

    /**
     * 点评内容
     */
    @TableField("comment")
    private String comment;

    /**
     * 点评时间
     */
    @TableField("comment_time")
    private LocalDateTime commentTime;

    /**
     * 点评老师ID
     */
    @TableField("comment_teacher")
    private Long commentTeacher;

    /**
     * 作业图片（多张图片用逗号分隔）
     */
    @TableField("images")
    private String images;
}
