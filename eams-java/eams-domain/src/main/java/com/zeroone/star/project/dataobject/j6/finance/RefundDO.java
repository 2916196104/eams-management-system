package com.zeroone.star.project.dataobject.j6.finance;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * <p>
 * 学员退款记录 数据对象
 * </p>
 *
 * @description 对应数据库表 refund，用于财务模块-学员退款管理
 */
@Data
@TableName("refund")
public class RefundDO {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 学生ID
     */
    @TableField("student_id")
    private Long studentId;

    /**
     * 学生课程关联表ID
     */
    @TableField("student_course_id")
    private Long studentCourseId;

    /**
     * 退费办理人ID
     */
    @TableField("operator")
    private Long operator;

    /**
     * 退费金额（负数）
     */
    @TableField("refund_amount")
    private BigDecimal refundAmount;

    /**
     * 退费课时数
     */
    @TableField("refund_lesson_count")
    private Integer refundLessonCount;

    /**
     * 退费发起时间
     */
    @TableField("apply_time")
    private LocalDateTime applyTime;

    /**
     * 退费说明
     */
    @TableField("remark")
    private String remark;

    /**
     * 退费办完时间
     */
    @TableField("done_time")
    private LocalDateTime doneTime;

    /**
     * 类型
     */
    @TableField("type_num")
    private Integer typeNum;

    /**
     * 退款状态
     */
    @TableField("verify_state")
    private Integer verifyState;

    /**
     * 审核时间
     */
    @TableField("verify_time")
    private LocalDateTime verifyTime;

    /**
     * 审核人ID
     */
    @TableField("verify_staff")
    private Long verifyStaff;
}
