package com.zeroone.star.j5.courseschedule.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("subject")
public class Subject {
    @TableId(type = IdType.ASSIGN_ID)
    private Long id;
    private String name;

    @TableLogic
    private Integer deleted;
}