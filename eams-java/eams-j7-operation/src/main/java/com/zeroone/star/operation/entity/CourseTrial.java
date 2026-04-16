package com.zeroone.star.operation.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 课程体验卡
 * </p>
 *
 * @author zht
 * @since 2026-03-13
 */
@Getter
@Setter
@TableName("course_trial")
public class CourseTrial implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 课程
     */
    private Long courseId;

    /**
     * 名称
     */
    private String title;

    /**
     * 发行数量
     */
    private Integer quantity;

    /**
     * 剩余数量
     */
    private Integer remainingQuantity;

    /**
     * 课时数
     */
    private Integer lessonCount;

    /**
     * 领取后有效天数
     */
    private Integer expireDays;

    /**
     * 发行结束日期
     */
    private LocalDate endDate;

    /**
     * 启用状态
     */
    private Boolean state;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 添加时间
     */
    @TableField(fill = FieldFill.INSERT)
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    @TableField(fill = FieldFill.INSERT_UPDATE)
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    @TableField(fill = FieldFill.UPDATE)
    private Boolean deleted;

    /**
     * 创建者所属组织ID
     */
    private Long orgId;


}
