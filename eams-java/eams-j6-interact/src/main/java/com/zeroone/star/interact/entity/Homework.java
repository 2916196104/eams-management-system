package com.zeroone.star.interact.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import lombok.Data;

import java.time.LocalDateTime;


@Data
public class Homework {

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long classId;

    private String title;

    private String content;

    private Long creator;

    private Long editor;

    private LocalDateTime addTime;

    private LocalDateTime editTime;

    private Integer deleted;

    private Long orgId;

}
