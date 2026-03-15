package com.zeroone.star.project.po.schedule;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.Date;

@Data
@TableName("lesson_schedule_setting")
public class LessonScheduleSettingPO {
    @TableId("id")
    private Long id;

    @TableField("排课计划id")
    private Long scheduleId;

    @TableField("星期")
    private String weeks;

    @TableField("开始时间")
    private LocalDateTime startTime;

    @TableField("结束时间")
    private LocalDateTime endTime;

    @TableField("教室id")
    private Long roomId;
}
