package com.zeroone.star.j5.courseschedule.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：学员购课合同实体类
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Data
@TableName("student_course")
public class StudentCourse implements Serializable {
    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /** 学生id */
    private Long studentId;

    /** 课程id */
    private Long courseId;

    /** 科目id */
    private Long subjectId;

    /** 开始时间 */
    private LocalDate startDate;

    /** 过期日期 */
    private LocalDate expireDate;

    /** 备注 */
    private String remark;

    /** 购买总课次 */
    private Integer countLessonTotal;

    /** 已上课次 */
    private Integer countLessonComplete;

    /** 退款次数 */
    private Integer countLessonRefund;

    /** 套餐金额 */
    private BigDecimal courseAmount;

    /** 优惠金额 */
    private BigDecimal discountAmount;

    /** 成交/合约金额 */
    private BigDecimal amount;

    /** 实付金额 */
    private BigDecimal paidAmount;

    /** 是否付清 0-否 1-是 */
    private Boolean payOff;

    /** 经手人 */
    private Long operator;

    /** 创建人 */
    private Long creator;

    /** 录入时间 */
    private LocalDateTime addTime;

    /** 编辑人 */
    private Long editor;

    /** 编辑时间 */
    private LocalDateTime editTime;

    /** 删除标记 */
    @TableLogic
    private Boolean deleted;

    /** 审核状态 */
    private Integer verifyState;

    /** 不足时已提醒次数 */
    private Integer warningTimes;

    /** 消课优先级 */
    private Integer priority;

    /** 单价 */
    private BigDecimal unitPrice;

    /** 是否来自于体验试用 */
    private Boolean fromTrial;

    /** 报名老师所属组织ID */
    private Long orgId;
}
