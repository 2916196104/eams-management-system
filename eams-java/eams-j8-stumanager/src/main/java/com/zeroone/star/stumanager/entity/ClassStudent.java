package com.zeroone.star.stumanager.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 班级学员表
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Getter
@Setter
@TableName("class_student")
public class ClassStudent implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 班级id
     */
    private Long classId;

    /**
     * 学生id
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
    private Boolean deleted;

    /**
     * 备注信息
     */
    private String remark;

    /**
     * 默认消费课程
     */
    private Long consumeCourseId;


}
