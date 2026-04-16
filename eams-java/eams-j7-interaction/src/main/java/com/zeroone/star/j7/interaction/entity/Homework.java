package com.zeroone.star.j7.interaction.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * homework 表的实体类
 * </p>
 * @author lvincent
 * @since 2026-03-16
 */
@Data
@TableName("homework")
public class Homework implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long classId;

    private String title;

    private String content;

    private Long creator;

    private Long editor;

    private LocalDateTime addTime;

    private LocalDateTime editTime;

    private Boolean deleted;

    private Long orgId;
}
