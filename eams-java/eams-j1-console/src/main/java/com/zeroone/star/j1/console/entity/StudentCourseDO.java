package com.zeroone.star.j1.console.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.math.BigDecimal;
import java.util.Date;

/**
 * <p>
 * 报名签约表
 * </p>
 * @author hxb
 */
@Getter
@Setter
@TableName("student_course")
public class StudentCourseDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 学生id
     */
    private Long studentId;

    /**
     * 课程d
     */
    private Long courseId;

    /**
     * 科目id
     */
    private Long subjectId;

    /**
     * 开始时间
     */
    private Date startDate;

    /**
     * 过期日期
     */
    private Date expireDate;

    /**
     * 备注
     */
    private String remark;

    /**
     * 购买总课次
     */
    private Integer countLessonTotal;

    /**
     * 已上课次
     */
    private Integer countLessonComplete;

    /**
     * 退款次数
     */
    private Integer countLessonRefund;

    /**
     * 套餐金额
     */
    private BigDecimal courseAmount;

    /**
     * 优惠金额
     */
    private BigDecimal discountAmount;

    /**
     * 成交/合约金额
     */
    private BigDecimal amount;

    /**
     * 实付金额
     */
    private BigDecimal paidAmount;

    /**
     * 是否付清 0 否1是
     */
    private Integer payOff;

    /**
     * 经手人
     */
    private Long operator;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 录入时间
     */
    private Date addTime;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 编辑时间
     */
    private Date editTime;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 审核状态
     */
    private Integer verifyState;

    /**
     * 不足时已提醒次数
     */
    private Integer warningTimes;

    /**
     * 消课优先级
     */
    private Integer priority;

    /**
     * 单价
     */
    private BigDecimal unitPrice;

    /**
     * 是否来自于体验试用
     */
    private Integer fromTrial;

    /**
     * 报名老师所属组织ID
     */
    private Long orgId;
}
