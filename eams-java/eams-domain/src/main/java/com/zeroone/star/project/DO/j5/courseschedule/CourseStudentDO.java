package com.zeroone.star.project.DO.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * @author silvan
 * @description 课程-学生
 */
@TableName("course_student")
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
    * 学生id
    * */
    @TableField("student_id")
    private Long studentId;

    /*
     * 学生种类
     * 0 - 普通学生
     * 1 - 随课生
     */
    @TableField("student_type")
    private int studentType;

    @TableField("create_time")
    private LocalDateTime createTime;

    @TableField("update_time")
    private LocalDateTime updateTime;

    /*
    * 评价时间
    * */
    @TableField("evaluation_time")
    private LocalDateTime evaluationTime;

    /*
    逻辑删除
    1:未删除
    2:已删除
     */
    @TableLogic
    private int deleted=0;

    /*
     * 对学生的评价
     * */
    @TableField("evaluation")
    private String evaluation;

    /*
     * 是否完成评价
     * 0-未评价
     * 1-已评价
     */
    @TableField("is_evaluation")
    private int isEvaluated=0;

    /*
     * 教学得分(1-5)
     * */
    @TableField("score")
    private int score;
}
