package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@TableName("lesson_student")
public class LessonStudentDO {
    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;
    /**
     * 课程id
     */
    private Long lessonId;
    /**
     * 班级id为空表示调课生
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
     * 签到结果
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