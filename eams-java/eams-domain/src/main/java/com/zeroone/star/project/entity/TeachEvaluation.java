package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 学评教
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("teach_evaluation")
public class TeachEvaluation implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 课次 id
     */
    private Long lessonId;

    /**
     * 老师 id
     */
    private Long teacherId;

    /**
     * 综合评分
     */
    private Integer score1;

    /**
     * 课堂气氛
     */
    private Integer score2;

    /**
     * 授课态度
     */
    private Integer score3;

    /**
     * 教学效果
     */
    private Integer score4;

    /**
     * 评语
     */
    private String content;

    /**
     * 评价时间
     */
    private LocalDateTime addTime;

    /**
     * 学生 id
     */
    private Long studentId;

    /**
     * 是否匿名
     */
    private Integer anonymity;

    /**
     * 被评价老师所属组织 ID
     */
    private Long orgId;
}
