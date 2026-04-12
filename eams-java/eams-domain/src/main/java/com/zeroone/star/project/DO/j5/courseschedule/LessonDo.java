package com.zeroone.star.project.DO.j5.courseschedule;
import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;

/**
 * @author silvan
 * @description 课程表
 */
@TableName("lesson")
@Data
public class LessonDo {
    /**
     * 主键
     */
    @TableId(type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 课程标题
     */
    @TableField("title")
    private String title;

    /**
     * 课节数 第几节课
     */
    @TableField("sn")
    private Integer sn;

    /**
     * 课程id
     */
    @TableField("course_id")
    private Long courseId;

    /**
     * 编排计划id
     */
    @TableField("schedule_id")
    private Long scheduleId;

    /**
     * 班级id
     */
    @TableField("class_id")
    private Long classId;

    /**
     * 教室id
     */
    @TableField("room_id")
    private Long roomId;

    /**
     * 上课日期
     */
    @TableField("date")
    private LocalDate date;

    /**
     * 开始时间
     */
    @TableField("start_time")
    private LocalTime startTime;

    /**
     * 结束时间
     */
    @TableField("end_time")
    private LocalTime endTime;

    /**
     * 创建人
     */
    @TableField("creator")
    private Long creator;

    /**
     * 编辑者
     */
    @TableField("editor")
    private Long editor;

    /**
     * 添加时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 修改时间
     */
    @TableField("edit_time")
    private LocalDateTime editTime;

    /**
     * 删除标记（逻辑删除）
     */
    @TableLogic
    @TableField("deleted")
    private Byte deleted;

    /**
     * 应扣课次数
     */
    @TableField("dec_count")
    private Byte decCount;

    /**
     * 备注
     */
    @TableField("remark")
    private String remark;

    /**
     * 授课方式
     */
    @TableField("teach_type")
    private Byte teachType;

    /**
     * 是否开启试听
     */
    @TableField("on_trial")
    private Byte onTrial;

    /**
     * 试听结果
     */
    @TableField("trial_result")
    private String trialResult;

    /**
     * 课次状态
     */
    @TableField("state")
    private Byte state;

    /**
     * 结课时间
     */
    @TableField("close_time")
    private LocalDateTime closeTime;

    /**
     * 结课人
     */
    @TableField("close_operator")
    private Long closeOperator;

    /**
     * 主讲人(只用于数据权限)
     */
    @TableField("teacher_id")
    private Long teacherId;

    /**
     * 是否开放预约
     */
    @TableField("bookable")
    private Byte bookable;

    /**
     * 老师所属学校ID
     */
    @TableField("school_id")
    private Long schoolId;

    /**
     * 创建者所属组织ID
     */
    @TableField("org_id")
    private Long orgId;
}
//@Data
//@TableName("lesson")
//public class LessonDo {
//    @TableId(type = IdType.AUTO)
//    private Long id;                // 主键ID
//    private Long classId;           // 班级ID
//    private Long courseId;          // 课程ID
//    private Long teacherId;         // 老师ID
//    private Long subjectId;         // 科目ID
//    private Long classroomId;       // 教室ID
//    private LocalDate date;   // 上课日期
//    private LocalTime startTime;    // 开始时间
//    private LocalTime endTime;      // 结束时间
//
//}
