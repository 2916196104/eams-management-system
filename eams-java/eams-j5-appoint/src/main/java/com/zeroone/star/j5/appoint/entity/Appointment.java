package com.zeroone.star.j5.appoint.entity;

import java.io.Serializable;
import java.time.LocalDateTime;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 预约记录
 * </p>
 *
 * @author makise
 * @since 2026-03-23
 */
@Data
@TableName("appointment")
public class Appointment implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 试听课次
     */
    private Long lessonId;

    /**
     * 学员id
     */
    private Long studentId;

    /**
     * 预约时间
     */
    private LocalDateTime addTime;

    /**
     * 备注
     */
    private String remark;

    /**
     * 审核状态
     */
    private Integer verifyState;

    /**
     * 审核时间
     */
    private LocalDateTime verifyTime;

    /**
     * 审核人
     */
    private Long verifyStaff;

    /**
     * 审核内容
     */
    private String verifyRemark;

    /**
     * 所属课程
     */
    private Long courseId;

    /**
     * 学生所属学校ID
     */
    private Long schoolId;

    /**
     * 学生的顾问
     */
    private Long counselor;

    /**
     * 体验卡id 来自于体验卡的预约有
     */
    private Long trialId;

    /**
     * 消费体验卡领取记录id
     */
    private Long trialRecordId;


}
