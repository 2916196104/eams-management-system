package com.zeroone.star.operation.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 学生积分变动记录
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("student_credit_log")
public class StudentCreditLog implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 学生 id
     */
    private Long studentId;

    /**
     * 学生账号 id
     */
    private Long userId;

    /**
     * 变动数量
     */
    private Integer credit;

    /**
     * 剩余积分数量
     */
    private Integer currentCredit;

    /**
     * 变动类型
     */
    private Integer changeType;

    /**
     * 变动时间
     */
    private LocalDateTime addTime;

    /**
     * 其他说明
     */
    private String remark;

    /**
     * 记录来源 id
     */
    private Long sourceId;

    /**
     * 调整人
     */
    private Long staffId;

    /**
     * 学生所属学校 ID
     */
    private Long schoolId;
}
