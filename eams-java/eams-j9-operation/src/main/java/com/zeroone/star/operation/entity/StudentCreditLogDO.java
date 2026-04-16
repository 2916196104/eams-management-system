package com.zeroone.star.operation.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * 学生积分变动记录实体
 */
@Getter
@Setter
@TableName("student_credit_log")
public class StudentCreditLogDO implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long studentId;

    private Long userId;

    private Integer credit;

    private Integer currentCredit;

    private Integer changeType;

    private LocalDateTime addTime;

    private String remark;

    private Long sourceId;

    private Long staffId;

    private Long schoolId;
}
