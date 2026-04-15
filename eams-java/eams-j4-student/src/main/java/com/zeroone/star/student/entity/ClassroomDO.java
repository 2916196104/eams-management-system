package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;
import java.time.LocalDateTime;

/**
 * 教室 DO
 */
@Data
@TableName("classroom")
public class ClassroomDO {
    @TableId(type = IdType.AUTO)
    private Long id;

    private String name;

    private String address;

    private Integer area;

    private String remark;

    private Long creator;

    private Long editor;

    private LocalDateTime addTime;

    private LocalDateTime editTime;

    @TableLogic
    private Integer deleted;

    private Long schoolId;

    private Long orgId;
}