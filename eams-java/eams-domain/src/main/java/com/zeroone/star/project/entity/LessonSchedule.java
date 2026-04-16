package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 排课计划
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("lesson_schedule")
public class LessonSchedule implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 班级 id
     */
    private Long classId;

    /**
     * 课程 id
     */
    private Long courseId;

    /**
     * 上课老师
     */
    private String teacherIds;

    /**
     * 助教
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
     * 排除节日
     */
    private Integer excludeHoliday;

    /**
     * 是否生成课表
     */
    private Integer state;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑者
     */
    private Long editor;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;

    /**
     * 修改时间
     */
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 冲突的 id 列表 空字符表示无冲突 null 是未检查
     */
    private String conflictIds;

    /**
     * 创建者所属组织 ID
     */
    private Long orgId;
}
