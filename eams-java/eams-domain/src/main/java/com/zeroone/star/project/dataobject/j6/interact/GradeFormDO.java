package com.zeroone.star.project.dataobject.j6.interact;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;
import lombok.Synchronized;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 成绩单 数据对象
 * </p>
 *
 * @description 对应数据库表 grade，用于互动模块-成绩单功能
 */
@Data
@TableName("grade")
public class GradeFormDO implements Serializable {
    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 成绩项目标题
     */
    @TableField("title")
    private String title;

    /**
     * 成绩项目说明
     */
    @TableField("info")
    private String info;


    /**
     * 创建人ID
     */
    @TableField(value = "creator",fill = FieldFill.INSERT)
    private Long creator;

    /**
     * 编辑人ID
     */
    @TableField(value = "editor",fill = FieldFill.INSERT_UPDATE)
    private Long editor;

    /**
     * 添加时间
     */
    @TableField(value = "add_time",fill = FieldFill.INSERT)
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    @TableField(value = "edit_time", fill = FieldFill.INSERT_UPDATE)
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
    @TableField(value = "org_id",fill = FieldFill.INSERT)
    private Long orgId;
}
