package com.zeroone.star.course.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 课程评价
 * </p>
 *
 * @author xxxcr
 * @since 2026-03-21
 */
@Getter
@Setter
@TableName("course_comment")
public class CourseCommentDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 所属课程
     */
    private Long courseId;

    /**
     * 学生id
     */
    private Long studentId;

    /**
     * 订单id
     */
    private Long orderId;

    /**
     * 章节标题
     */
    private String content;

    /**
     * 打分
     */
    private Integer score;

    /**
     * 发布状态
     */
    private Boolean state;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    private Boolean deleted;


}
