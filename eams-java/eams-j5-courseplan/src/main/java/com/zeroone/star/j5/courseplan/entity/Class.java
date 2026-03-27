package com.zeroone.star.j5.courseplan.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 班级信息实体类
 * </p>
 *
 * @author taohu5564
 * @since 2026-03-17
 */
@Data
@TableName("class")
public class Class {
    /**
     * 主键 ID (bigint unsigned)
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 班级名
     */
    private String name;

    /**
     * 课程 ID (关联课程表)
     */
    private Long courseId;

    /**
     * 教室 ID (关联教室表)
     */
    private Long classroomId;

    /**
     * 创建人 ID
     */
    @TableField(fill = FieldFill.INSERT)
    private Long creator;

    /**
     * 编辑者 ID
     */
    @TableField(fill = FieldFill.INSERT_UPDATE)
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
     * 删除标记 (0:未删除, 1:已删除)
     * MyBatis-Plus 会自动处理逻辑删除
     */
    @TableLogic
    private Integer deleted;

    /**
     * 班级负责人 ID (关联教师表)
     */
    private Long teacherId;

    /**
     * 排课备注
     */
    private String remark;

    /**
     * 是否完结 (0:进行中, 1:已完结)
     */
    private Integer beOver;

    /**
     * 完结时间
     */
    private LocalDateTime overTime;

    /**
     * 完结操作人 ID
     */
    private Long overOperator;

    /**
     * 计划开班日期
     */
    private LocalDate startDate;

    /**
     * 计划结业日期
     */
    private LocalDate endDate;

    /**
     * 预招人数
     */
    private Integer plannedStudentCount;

    /**
     * 预排课次数
     */
    private Integer plannedLessonCount;

    /**
     * 创建者所属学校 ID
     */
    private Long schoolId;

    /**
     * 创建者所属组织 ID (多租户/数据权限关键字段)
     */
    private Long orgId;

    /**
     * 年级 ID
     */
    private Integer gradeId;
}
