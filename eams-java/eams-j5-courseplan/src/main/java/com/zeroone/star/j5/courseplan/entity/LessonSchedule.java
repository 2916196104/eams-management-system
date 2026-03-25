package com.zeroone.star.j5.courseplan.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 排课计划表 实体类
 * </p>
 *
 * @author taohu5564
 * @since 2026-03-16
 */
@Data
@TableName("lesson_schedule")
public class LessonSchedule {
    /**
     * 主键 ID
     */
    @TableId(value = "id", type = IdType.AUTO) // 假设是自增，如果是雪花算法改为 IdType.ASSIGN_ID
    private Long id;

    /**
     * 班级 ID
     */
    private Long classId;

    /**
     * 课程 ID
     */
    private Long courseId;

    /**
     * 上课老师 (多个ID通常用逗号分隔存储，如 "1,2,3")
     */
    private String teacherIds;

    /**
     * 助教 (多个ID通常用逗号分隔存储)
     */
    private String assistantIds;

    /**
     * 开始日期
     */
    private LocalDate startDate;

    /**
     * 结束日期
     */
    private LocalDate endDate;

    /**
     * 学员扣课次数
     */
    private Integer decLessonCount;

    /**
     * 排课次数
     */
    private Integer times;

    /**
     * 排除节日 (1:是, 0:否)
     */
    private Integer excludeHoliday;

    /**
     * 是否生成课表 (1:是, 0:否)
     */
    private Integer state;

    /**
     * 创建人 ID
     * 自动填充：插入时自动填入当前用户ID
     */
    @TableField(fill = FieldFill.INSERT)
    private Long creator;

    /**
     * 编辑者 ID
     * 自动填充：更新时自动填入当前用户ID
     */
    @TableField(fill = FieldFill.INSERT_UPDATE)
    private Long editor;

    /**
     * 添加时间
     * 自动填充：插入时自动填入当前时间
     */
    @TableField(fill = FieldFill.INSERT)
    private LocalDateTime addTime;

    /**
     * 修改时间
     * 自动填充：更新时自动填入当前时间
     */
    @TableField(fill = FieldFill.INSERT_UPDATE)
    private LocalDateTime editTime;

    /**
     * 删除标记 (0:未删除, 1:已删除)
     * MyBatis-Plus 逻辑删除注解
     */
    @TableLogic
    private Integer deleted;

    /**
     * 冲突的 ID 列表 (空字符表示无冲突，null 表示未检查)
     * 数据库类型为 text
     */
    private String conflictIds;

    /**
     * 创建者所属组织 ID
     */
    private Long orgId;
}
