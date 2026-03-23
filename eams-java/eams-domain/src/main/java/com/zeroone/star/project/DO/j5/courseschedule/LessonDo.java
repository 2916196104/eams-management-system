package com.zeroone.star.project.DO.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalTime;

@Data
@TableName("lesson")
public class LessonDo {
    @TableId(type = IdType.AUTO)
    private Long id;                // 主键ID
    private String title;           // 课程标题
    private Integer state;          // 状态
    private Long schoolId;          // 学校ID
    private Long roomId;           // 教室ID
    private Integer decCount;       // 消课基数
    private Integer bookable;       // 是否可预约
    private Long classId;           // 班级ID
    private Long courseId;          // 课程ID
    private Long teacherId;         // 老师ID
    private LocalDate date;   // 上课日期
    private LocalTime startTime;    // 开始时间
    private LocalTime endTime;      // 结束时间

}
