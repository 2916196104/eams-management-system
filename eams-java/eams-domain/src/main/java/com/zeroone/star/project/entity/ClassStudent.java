package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 班级学员表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("class_student")
public class ClassStudent implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 班级 id
     */
    private Long classId;

    /**
     * 学生 id
     */
    private Long studentId;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 加入原因
     */
    private Integer reason;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 备注信息
     */
    private String remark;

    /**
     * 默认消费课程
     */
    private Long consumeCourseId;
}
