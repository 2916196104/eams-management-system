package com.zeroone.star.j5.courseschedule.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：课次变更记录实体类
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Data
@TableName("student_lesson_count_log")
public class StudentLessonCountLog implements Serializable {
    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /** 学员id */
    private Long studentId;

    /** 课程id */
    private Long courseId;

    /** 课次id */
    private Long lessonId;

    /** 变更课次数 */
    private Integer changeCount;

    /** 剩余数量 */
    private Integer remainingCount;

    /** 操作人 */
    private Long staffId;

    /** 时间 */
    private LocalDateTime addTime;

    /** 变更阶段 1-课程报名 2-上课消课 3-后台操作 4-退课 5-退课驳回 6-取消消课 */
    private Integer stage;

    /** 备注 */
    private String remark;
}
