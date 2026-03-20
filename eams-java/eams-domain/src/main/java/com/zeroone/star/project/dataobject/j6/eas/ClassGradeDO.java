package com.zeroone.star.project.dataobject.j6.eas;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 年级表 数据对象
 * </p>
 *
 * @description 对应数据库表 class_grade，用于教务-年级管理模块
 */
@Data
@TableName("class_grade")
public class ClassGradeDO {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 年级名称
     */
    @TableField("name")
    private String name;

    /**
     * 入学年份
     */
    @TableField("year")
    private Integer year;

    /**
     * 备注
     */
    @TableField("remark")
    private String remark;

    /**
     * 排序值
     */
    @TableField("sort_num")
    private Integer sortNum;

    /**
     * 创建人ID
     */
    @TableField("creator")
    private Long creator;

    /**
     * 编辑人ID
     */
    @TableField("editor")
    private Long editor;

    /**
     * 添加时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    @TableField("edit_time")
    private LocalDateTime editTime;

    /**
     * 删除标记（0-未删除，1-已删除）
     */
    @TableLogic
    @TableField("deleted")
    private Integer deleted;
}
