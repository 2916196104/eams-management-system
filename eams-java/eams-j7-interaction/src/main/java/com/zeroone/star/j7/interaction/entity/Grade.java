package com.zeroone.star.j7.interaction.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 成绩单
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("grade")
public class Grade implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 成绩项目标题
     */
    private String title;

    /**
     * 成绩项目说明
     */
    private String info;

    /**
     * 创建者
     */
    private Long creator;

    /**
     * 创建时间
     */
    private LocalDateTime addTime;

    /**
     * 逻辑删除
     */
    private Integer deleted;

    /**
     * 编辑者
     */
    private Long editor;

    /**
     * 编辑时间
     */
    private LocalDateTime editTime;

    /**
     * 创建者所属组织 ID
     */
    private Long orgId;
}
