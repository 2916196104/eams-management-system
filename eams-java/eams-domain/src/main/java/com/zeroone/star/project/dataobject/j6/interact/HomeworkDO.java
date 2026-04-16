package com.zeroone.star.project.dataobject.j6.interact;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 作业 数据对象
 * </p>
 *
 * @description 对应数据库表 homework，用于互动模块-作业管理功能
 */
@Data
@TableName("homework")
public class HomeworkDO {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 班级ID
     */
    @TableField("class_id")
    private Long classId;

    /**
     * 作业标题
     */
    @TableField("title")
    private String title;

    /**
     * 作业内容
     */
    @TableField("content")
    private String content;

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

    /**
     * 创建者所属组织ID
     */
    @TableField("org_id")
    private Long orgId;
}
