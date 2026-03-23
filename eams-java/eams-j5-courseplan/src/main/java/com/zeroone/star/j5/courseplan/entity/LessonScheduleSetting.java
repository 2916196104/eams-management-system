package com.zeroone.star.j5.courseplan.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalTime;

/**
 * <p>
 * 排课计划明细/设置表
 * 存储具体的上课时间规则（周几、几点、教室）
 * </p>
 *
 * @author taohu5564
 * @since 2026-03-19
 */
@Data
@TableName("lesson_schedule_setting")
public class LessonScheduleSetting {

    /**
     * 主键 ID
     * 对应数据库: id (bigint unsigned)
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 编排计划 ID (关联主表 lesson_schedule.id)
     * 对应数据库: schedule_id (bigint)
     */
    private Long scheduleId;

    /**
     * 星期
     * 对应数据库: weeks (varchar(30))
     * 建议存储格式: "1,3,5" 或 "一,三,五"，具体看业务约定
     */
    private String weeks;

    /**
     * 开始时间
     * 对应数据库: start_time (time)
     * 使用 LocalTime 映射 SQL TIME 类型
     */
    private LocalTime startTime;

    /**
     * 结束时间
     * 对应数据库: end_time (time)
     */
    private LocalTime endTime;

    /**
     * 教室 ID
     * 对应数据库: room_id (bigint unsigned)
     */
    private Long roomId;
}

