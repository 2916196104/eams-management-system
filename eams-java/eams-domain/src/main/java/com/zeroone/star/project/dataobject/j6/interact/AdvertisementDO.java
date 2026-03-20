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
 * 通知管理/广告 数据对象
 * </p>
 *
 * @description 对应数据库表 advertisement，用于互动模块-通知管理功能
 *              支持类型：学生端首页Banner、学生端首页提示、学生端首页弹窗
 */
@Data
@TableName("advertisement")
public class AdvertisementDO {

    /**
     * 主键ID
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 发送标题
     */
    @TableField("title")
    private String title;

    /**
     * 类型（1-学生端首页Banner，2-学生端首页提示，3-学生端首页弹窗）
     */
    @TableField("type")
    private Integer type;

    /**
     * 发送内容
     */
    @TableField("content")
    private String content;

    /**
     * 封面图片地址
     */
    @TableField("cover")
    private String cover;

    /**
     * 创建者ID
     */
    @TableField("creator")
    private Long creator;

    /**
     * 创建时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 删除标记（0-未删除，1-已删除）
     */
    @TableLogic
    @TableField("deleted")
    private Integer deleted;

    /**
     * 编辑时间
     */
    @TableField("edit_time")
    private LocalDateTime editTime;

    /**
     * 编辑者ID
     */
    @TableField("editor")
    private Long editor;

    /**
     * 状态（0-禁用，1-启用）
     */
    @TableField("state")
    private Integer state;

    /**
     * 排序值
     */
    @TableField("sort_num")
    private Integer sortNum;

    /**
     * 唯一码
     */
    @TableField("code")
    private String code;
}
