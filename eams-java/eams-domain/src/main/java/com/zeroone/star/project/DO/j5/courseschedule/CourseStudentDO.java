package com.zeroone.star.project.DO.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * @author silvan
 * @description 课程-学生
 */
@TableName("lesson_student")
@Data
public class CourseStudentDO {

    @TableId(type=IdType.ASSIGN_ID)
    private Long id;

    /*
    * 课程id
    * */
    @TableField("lesson_id")
    private Long lessonId;

    /*
    * 班级id
    * */
    private Integer classId;

    /*
     * 学生id
     * */
    @TableField("student_id")
    private Long studentId;

    /*
    * 实扣课次
    * */
    @TableField("dec_lesson_count")
    private Integer decLessonCount;


    /*
    * 应扣课次
    * */
    @TableField("lesson_count")
    private Integer lessonCount;

    /*
    * 点名的老师
    * */
    @TableField("teacher_id")
    private Long teacherId;

    /*
    * 签到时间
    * */
    @TableField("sign_time")
    private LocalDateTime signTime;

    /*
    * 签到方式
    * */
    @TableField("sign_type")
    private Byte signType;

    /*
    * 签到结果
    * */
    @TableField("sign_state")
    private Byte signState;

    /*
     * 老师评分(1-5)
     * */
    @TableField("score")
    private Integer score;

    /*
     * 对学生的评价
     * */
    @TableField("evaluation")
    private String evaluation;

    /*
    * 评价时间
    * */
    @TableField("evaluate_time")
    private LocalDateTime evaluationTime;

    /*
    * 评价老师
    * */
    @TableField("evaluate_teacher")
    private Long evaluateTeacher;


    /*
    * 实际消费课程
    * */
    @TableField("consume_course_id")
    private Long consumeCourseId;

    /*
    * 消费课程与学生关联表id
    * */
    @TableField("consume_student_course_id")
    private Long consumeStudentCourseId;

    /*
    * 学生的顾问
    * */
    @TableField("counselor")
    private Long counselor;

    /*
    * 加入时间
    * */
    @TableField("add_time")
    private LocalDateTime addTime;

    /*
    * 上课老师所属组织id
    * */
    @TableField("org_id")
    private Long orgId;


}
