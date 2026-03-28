package com.zeroone.star.j5.courseplan.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：课次学员关联实体类
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Data
@TableName("lesson_student")
public class LessonStudent implements Serializable {
    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /** 课次id */
    private Long lessonId;

    /** 班级id 为空表示调课生 */
    private Long classId;

    /** 学员id */
    private Long studentId;

    /** 实扣课次 */
    private Integer decLessonCount;

    /** 应扣课次 */
    private Integer lessonCount;

    /** 点名的老师 */
    private Long teacherId;

    /** 签到时间 */
    private LocalDateTime signTime;

    /** 签到方式 */
    private Integer signType;

    /** 签到结果 0-未签到 1-已签到 2-迟到签到 3-请假 4-旷课 */
    private Integer signState;

    /** 老师评分 */
    private Integer score;

    /** 老师评语 */
    private String evaluation;

    /** 评语时间 */
    private LocalDateTime evaluateTime;

    /** 评语老师 */
    private Long evaluateTeacher;

    /** 实际消费课程 */
    private Long consumeCourseId;

    /** 消费课程与学生关联表ID */
    private Long consumeStudentCourseId;

    /** 学生的顾问 */
    private Long counselor;

    /** 加入时间 */
    private LocalDateTime addTime;

    /** 上课老师所属组织ID */
    private Long orgId;
}
