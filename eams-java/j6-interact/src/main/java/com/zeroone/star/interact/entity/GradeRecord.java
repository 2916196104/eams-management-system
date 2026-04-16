package com.zeroone.star.interact.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述:
 * </p>
 *
 * @author upup
 * @version 1.0.0
 * @since 2026-03-22
 */

@Data
public class GradeRecord implements Serializable {
    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;
    /**
     * 考核项id
     */

    private Long gradeId;
    /**
     * 学生id
     */

    private Long studentId;
    /**
     *  分数
     * */

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
