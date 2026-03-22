package com.zeroone.star.project.DO.j5.appoint;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;


import java.time.LocalDateTime;

@Data
@TableName("appointment")
public class AppointmentDO {

    /**
     * 主键
     */
    @TableId(type = IdType.AUTO)
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