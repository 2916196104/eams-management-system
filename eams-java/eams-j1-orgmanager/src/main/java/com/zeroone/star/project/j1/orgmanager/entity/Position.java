package com.zeroone.star.project.j1.orgmanager.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：职位表DO
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
@Data
@TableName("staff_position")
public class Position {
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    @TableField("name")
    private String name;

    @TableField("add_time")
    private LocalDateTime addTime;

    @TableField("edit_time")
    private LocalDateTime editTime;

    @TableField("creator")
    private Long creator;

    @TableField("editor")
    private Long editor;
}
