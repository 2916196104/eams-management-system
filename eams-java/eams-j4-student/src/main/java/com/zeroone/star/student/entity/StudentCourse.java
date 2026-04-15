package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：学员签约记录实体
 * </p>
 */
@Data
@TableName("student_course")
public class StudentCourse implements Serializable {
    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
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
    private LocalDate startDate;
    /**
     * 过期日期
     */
    private LocalDate expireDate;
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
    private Boolean payOff;
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
    private LocalDateTime addTime;
    /**
     * 编辑人
     */
    private Long editor;
    /**
     * 编辑时间
     */
    private LocalDateTime editTime;
    /**
     * 删除标记
     */
    private Boolean deleted;
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
    private Boolean fromTrial;
    /**
     * 报名老师所属组织ID
     */
    private Long orgId;
    // 数据库不存在，仅用于展示
    @TableField(exist = false)
    private String name;      // 学员姓名
    @TableField(exist = false)
    private String mobile;    // 家长手机号
    @TableField(exist = false)
    private String courseName;// 课程名称（来自 course.name）
    @TableField(exist = false)
    private Integer lessonCount;
    @TableField(exist = false)
    private Integer completeLessonCount;
    @TableField(exist = false)
    private Integer remainingLessonCount;
    @TableField(exist = false)
    private Integer decLessonCount;
}
