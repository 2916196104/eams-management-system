package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.io.Serializable;
import java.util.Date;

/**
 * 班级表 DO
 * 对应数据库表：class（Class是Java关键字，类名用ClassInfo）
 */
@Data
@TableName("class") // 映射数据库表名：class
public class ClassInfo implements Serializable {
    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(type = IdType.AUTO)
    private Long id;

    /**
     * 班级名称
     */
    private String class_name;

    /**
     * 班级编码
     */
    private String class_code;

    /**
     * 课程id
     */
    private Long course_id;

    /**
     * 授课老师id
     */
    private Long teacher_id;

    /**
     * 班级状态（0-未开班，1-在读，2-已结业）
     */
    private Integer state;

    /**
     * 开班时间
     */
    private Date start_time;

    /**
     * 结业时间
     */
    private Date end_time;

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