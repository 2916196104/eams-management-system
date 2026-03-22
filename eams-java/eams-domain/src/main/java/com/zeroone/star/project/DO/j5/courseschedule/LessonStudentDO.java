package com.zeroone.star.project.DO.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 课次学生关联实体
 * 对应数据库表：lesson_student
 */
@Data
@TableName("lesson_student")
public class LessonStudentDO {

    /**
     * 主键
     * 使用 ASSIGN_ID 分布式ID生成策略
     */
    @TableId(type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 课次id
     */
    private Long lessonId;

    /**
     * 班级id，为空表示调课生
     */
    private Integer classId;

    /**
     * 学员id
     */
    private Long studentId;

    /**
     * 实扣课次
     */
    private Integer decLessonCount;

    /**
     * 应扣课次
     */
    private Integer lessonCount;

    /**
     * 点名的老师
     */
    private Long teacherId;

    /**
     * 签到时间
     */
    private LocalDateTime signTime;

    /**
     * 签到方式
     */
    private Integer signType;

    /**
     * 签到结果 0-未签到 1-已签到 2-迟到签到 3-请假 4-旷课
     */
    private Integer signState;

    /**
     * 老师评分
     */
    private Integer score;

    /**
     * 老师评语
     */
    private String evaluation;

    /**
     * 评语时间
     */
    private LocalDateTime evaluateTime;

    /**
     * 评语老师
     */
    private Long evaluateTeacher;

    /**
     * 实际消费课程
     */
    private Long consumeCourseId;

    /**
     * 消费课程与学生关联表ID
     */
    private Long consumeStudentCourseId;

    /**
     * 学生的顾问
     */
    private Long counselor;

    /**
     * 加入时间
     */
    private LocalDateTime addTime;

    /**
     * 上课老师所属组织ID
     */
    private Long orgId;
}
