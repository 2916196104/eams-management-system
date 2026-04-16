package com.zeroone.star.project.dataobject.j6.interact;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * 课时学生关联数据对象（对应表：lesson_student）
 */
@Data
@TableName("lesson_student")
public class LessonStudentDO implements Serializable {
    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 课次id
     */
    @TableField("lesson_id")
    private Long lessonId;

    /**
     * 班级id
     */
    @TableField("class_id")
    private Integer classId;

    /**
     * 学生id
     */
    @TableField("student_id")
    private Long studentId;

    /**
     * 实扣课次
     */
    @TableField("dec_lesson_count")
    private Integer decLessonCount;

    /**
     * 应扣课次
     */
    @TableField("lesson_count")
    private Integer lessonCount;

    /**
     * 教师id
     */
    @TableField("teacher_id")
    private Long teacherId;

    /**
     * 签到时间
     */
    @TableField("sign_time")
    private LocalDateTime signTime;

    /**
     * 签到方式
     */
    @TableField("sign_type")
    private Integer signType;

    /**
     * 签到结果
     */
    @TableField("sign_state")
    private Integer signState;

    /**
     * 老师评分
     */
    @TableField("score")
    private Integer score;

    /**
     * 老师评语
     */
    @TableField("evaluation")
    private String evaluation;

    /**
     * 评语时间
     */
    @TableField("evaluate_time")
    private LocalDateTime evaluateTime;

    /**
     * 评语老师
     */
    @TableField("evaluate_teacher")
    private Long evaluateTeacher;

    /**
     * 实际消费课程
     */
    @TableField("consume_course_id")
    private Long consumeCourseId;

    /**
     * 消费课程与学生关联表ID
     */
    @TableField("consume_student_course_id")
    private Long consumeStudentCourseId;

    /**
     * 学生的顾问
     */
    @TableField("counselor")
    private Long counselor;

    /**
     * 加入时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 上课老师所属组织ID
     */
    @TableField("org_id")
    private Long orgId;
}
