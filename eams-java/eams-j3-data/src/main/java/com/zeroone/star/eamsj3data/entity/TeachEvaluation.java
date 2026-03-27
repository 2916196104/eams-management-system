package com.zeroone.star.eamsj3data.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;


@Data
public class TeachEvaluation implements Serializable {
    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 课程id
     */
    private Long lessonId;

    /**
     * 教师id
     */
    private Long teacherId;

    /**
     * 评分项1
     */
    private Integer score1;

    /**
     * 评分项2
     */
    private Integer score2;

    /**
     * 评分项3
     */
    private Integer score3;

    /**
     * 评分项4
     */
    private Integer score4;

    /**
     * 评价内容
     */
    private String content;

    /**
     * 提交时间
     */
    @TableField(fill = FieldFill.INSERT)
    private LocalDateTime addTime;

    /**
     * 学生id
     */
    private Long studentId;

    /**
     * 是否匿名(0否 1是)
     */
    private Boolean anonymity;

    /**
     * 组织id
     */
    private Long orgId;
}
