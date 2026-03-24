package com.zeroone.star.j5.classmanager.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;
import lombok.experimental.Accessors;

/**
 * <p>
 * 班级学员表
 * </p>
 *
 * @author j5-luohan
 * @since 2026-03-23
 */
@Getter
@Setter
@Accessors(chain = true)
@TableName("class_student")
public class ClassStudent implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId("id")
    private Long id;

    /**
     * 班级id
     */
    @TableField("class_id")
    private Long classId;

    /**
     * 学生id
     */
    @TableField("student_id")
    private Long studentId;

    /**
     * 添加时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 创建人
     */
    @TableField("creator")
    private Long creator;

    /**
     * 加入原因
     */
    @TableField("reason")
    private Integer reason;

    /**
     * 删除标记
     */
    @TableField("deleted")
    private Boolean deleted;

    /**
     * 备注信息
     */
    @TableField("remark")
    private String remark;

    /**
     * 默认消费课程
     */
    @TableField("consume_course_id")
    private Long consumeCourseId;


}
