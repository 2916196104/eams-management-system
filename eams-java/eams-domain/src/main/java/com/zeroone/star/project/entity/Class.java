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
 * 班级
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("class")
public class Class implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 班级名
     */
    private String name;

    /**
     * 课程
     */
    private Long courseId;

    /**
     * 教室
     */
    private Long classroomId;

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
     * 编辑时间
     */
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 班级负责人
     */
    private Long teacherId;

    /**
     * 排课备注
     */
    private String remark;

    /**
     * 是否完结
     */
    private Integer beOver;

    /**
     * 完结时间
     */
    private LocalDateTime overTime;

    /**
     * 完结操作人
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
     * 创建者所属学校 id
     */
    private Long schoolId;

    /**
     * 创建者所属组织 ID
     */
    private Long orgId;

    /**
     * 年级 ID
     */
    private Integer gradeId;
}
