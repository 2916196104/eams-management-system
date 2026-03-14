package com.zeroone.star.stumanager.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 学生积分变动记录
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Getter
@Setter
@TableName("student_credit_log")
public class StudentCreditLog implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 学生id
     */
    private Long studentId;

    /**
     * 学生账号id
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
     * 记录来源id
     */
    private Long sourceId;

    /**
     * 调整人
     */
    private Long staffId;

    /**
     * 学生所属学校ID
     */
    private Long schoolId;


}
