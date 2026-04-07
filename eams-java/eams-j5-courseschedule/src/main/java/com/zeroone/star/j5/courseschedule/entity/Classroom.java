package com.zeroone.star.j5.courseschedule.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@TableName("classroom")
public class Classroom {
    @TableId(type = IdType.ASSIGN_ID)
    private Long id;
    private String name;
    private String address;
    private LocalDateTime addTime;

    @TableLogic
    private Integer deleted;
}
