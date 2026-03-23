package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * student_Credit_Log
 */
@Data
@TableName("student_credit_log")
public class StudentCreditLog {
    /**
     * 主键
     */
    @TableId(type = IdType.AUTO)
    private Long id;
    /**
     * 学生id
     */
    private int student_id;
    /**
     * 学生账号id
     */
    private int user_id;
    /**
     * 变动数量
     */
    private int credit;
    /**
     * 剩余积分数量
     */
    private int current_credit;
    /**
     * 变动类型
     */
    private int change_type;
    /**
     * 变动时间
     */
    private LocalDateTime add_time;
    /**
     * 其他说明
     */
    private String remark;
    /**
     * 记录来源id
     */
    private int source_id;
    /**
     * 调整人
     */
    private int staff_id;
    /**
     * 学生所属学校ID
     */
    private int school_id;
}
