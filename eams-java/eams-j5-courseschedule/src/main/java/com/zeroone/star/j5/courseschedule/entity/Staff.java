package com.zeroone.star.j5.courseschedule.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@TableName("staff")
public class Staff {
    @TableId(type = IdType.ASSIGN_ID)
    private Long id;
    private String name;
    private String mobile;
    private Integer gender;
    private String headImg;
    private LocalDateTime addTime;
    private LocalDateTime editTime;

    @TableLogic
    private Integer deleted;
}