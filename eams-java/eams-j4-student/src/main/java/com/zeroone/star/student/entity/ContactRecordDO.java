package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;
import java.time.LocalDateTime;

/**
 * 学员跟进记录 DO
 */
@Data
@TableName("contact_record")
public class ContactRecordDO {
    @TableId(type = IdType.ASSIGN_ID)
    private Long id;

    private Long studentId;

    private String info;

    private LocalDateTime contactTime;

    private LocalDateTime contactNextTime;

    private Integer contactType;

    private String contactPhone;

    private Long creator;

    private LocalDateTime addTime;

    private Integer stage;

    @TableLogic
    private Integer deleted;

    private Long orgId;
}