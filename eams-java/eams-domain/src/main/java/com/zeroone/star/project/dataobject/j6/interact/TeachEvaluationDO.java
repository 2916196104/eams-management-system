package com.zeroone.star.project.dataobject.j6.interact;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 学评教 数据对象
 * </p>
 *
 * @description 对应数据库表 teach_evaluation，用于互动模块-学生评价老师教学功能
 */
@Data
@TableName("teach_evaluation")
public class TeachEvaluationDO {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 课次ID
     */
    @TableField("lesson_id")
    private Long lessonId;

    /**
     * 老师ID
     */
    @TableField("teacher_id")
    private Long teacherId;

    /**
     * 综合评分
     */
    @TableField("score1")
    private Integer score1;

    /**
     * 课堂气氛评分
     */
    @TableField("score2")
    private Integer score2;

    /**
     * 授课态度评分
     */
    @TableField("score3")
    private Integer score3;

    /**
     * 教学效果评分
     */
    @TableField("score4")
    private Integer score4;

    /**
     * 评语内容
     */
    @TableField("content")
    private String content;

    /**
     * 评价时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 学生ID
     */
    @TableField("student_id")
    private Long studentId;

    /**
     * 是否匿名（0-否，1-是）
     */
    @TableField("anonymity")
    private Integer anonymity;

    /**
     * 被评价老师所属组织ID
     */
    @TableField("org_id")
    private Long orgId;
}
