package com.zeroone.star.project.dataobject.j6.interact;
import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;
import java.io.Serializable;
import java.time.LocalDateTime;
/**
 * <p>
 * 成绩单 数据对象
 * </p>
 *
 * @description 对应数据库表 grade，用于互动模块-成绩单
 */
@Data
@TableName("grade")
public class GradeDO implements Serializable {
    /**
     * 主键
     */
    @TableId(value = "id",type = IdType.ASSIGN_ID)
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
     * 创建者
     */
    @TableField("creator")
    private Long creator;
    /**
     * 创建时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;
    /**
     * 逻辑删除
     */
    @TableLogic
    @TableField("deleted")
    private Integer deleted;
    /**
     * 编辑者
     */
    @TableField("editor")
    private Long editor;
    /**
     * 编辑时间
     */
    @TableField("edit_time")
    private LocalDateTime editTime;
    /**
     * 创建者所属组织ID
     */
    @TableField("org_id")
    private Long orgId;
}