package com.zeroone.star.project.entity.j1.orgmanager;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

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
