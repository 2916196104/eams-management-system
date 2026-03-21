package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.io.Serializable;
import java.util.Date;

/**
 * 班级学员关联表 DO
 * 对应数据库表：class_student
 */
@Data
@TableName("class_student")
public class ClassStudent implements Serializable {
    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(type = IdType.AUTO)
    private Long id;

    /**
     * 班级id
     */
    private Long class_id;

    /**
     * 学员id
     */
    private Long student_id;

    /**
     * 关联状态（0-退出，1-在读）
     */
    private Integer state;

    /**
     * 加入时间
     */
    private Date join_time;

    /**
     * 退出时间
     */
    private Date quit_time;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 创建时间
     */
    private Date add_time;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 编辑时间
     */
    private Date edit_time;

    /**
     * 删除标记（0-未删除，1-已删除）
     */
    @TableLogic
    private Integer deleted;

    /**
     * 所属组织ID
     */
    private Long org_id;
}