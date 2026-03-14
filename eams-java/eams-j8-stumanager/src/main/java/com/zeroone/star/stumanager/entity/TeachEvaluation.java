package com.zeroone.star.stumanager.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 学评教
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Getter
@Setter
@TableName("teach_evaluation")
public class TeachEvaluation implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 课次id
     */
    private Long lessonId;

    /**
     * 老师id
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
     * 学生id
     */
    private Long studentId;

    /**
     * 是否匿名
     */
    private Boolean anonymity;

    /**
     * 被评价老师所属组织ID
     */
    private Long orgId;


}
