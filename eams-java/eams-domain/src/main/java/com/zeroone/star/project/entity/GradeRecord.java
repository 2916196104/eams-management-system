package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 成绩单学生分数
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("grade_record")
public class GradeRecord implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 考核项 id
     */
    private Long gradeId;

    /**
     * 学生 id
     */
    private Long studentId;

    /**
     * 分数
     */
    private Integer score;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;

    /**
     * 添加人
     */
    private Long creator;
}
