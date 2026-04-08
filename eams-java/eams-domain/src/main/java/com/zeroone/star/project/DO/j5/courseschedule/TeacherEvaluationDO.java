package com.zeroone.star.project.DO.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import io.github.classgraph.json.Id;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.sql.Time;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * @author silvan
 * @description 教学评价表DO领域模型
 */

@Data
@TableName("teacher_evaluation")
public class TeacherEvaluationDO {

    /*
    * 主键ID
    * */
    @Id
    @TableField("id")
    private Long id;

    /*
    * 学生ID
    * */
    @TableField("student_id")
    private Long studentId;

    /*
    * 教师ID
    * */
    @TableField("teacher_id")
    private Long teacherId;


    /*
    * 课程ID
    * */
    @TableField("lesson_id")
    private Long lessonId;

    /*
    * 教学评价
    * */
    @TableField("content")
    private String content;

    /*
    * 教学得分(1-5)
    * */
    @TableField("score")
    private Integer score;

    /*
    * 创建时间
    * */
    @TableField("create_time")
    private LocalDate creatTime;

    /*
    * 更新时间
    * */
    @TableField("update_time")
    private LocalDate updateTime;

    /*
    * 是否匿名
    * 0-不匿名
    * 1-匿名
    * */
    @TableField("anonymity")
    private int anonymity;

    /*
    * 逻辑删除
    * 0-未删除
    * 1-已删除
    * */
    @TableLogic
    @TableField("deleted")
    private Integer deleted;

}
