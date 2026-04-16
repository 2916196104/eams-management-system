package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 积分记录
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("point_record")
public class PointRecord implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 学生 id
     */
    private Long studentId;

    /**
     * 变动积分
     */
    private Integer point;

    /**
     * 变动时间
     */
    private LocalDateTime addTime;

    /**
     * 变动阶段
     */
    private Integer stage;

    /**
     * 剩余积分
     */
    private Integer balance;

    /**
     * 详细信息
     */
    private String info;
}
