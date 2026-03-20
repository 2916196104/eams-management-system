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
 * 站内信 数据对象
 * </p>
 *
 * @description 对应数据库表 message，用于互动模块-站内信功能
 */
@Data
@TableName("message")
public class MessageDO {

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
     * 发送内容
     */
    @TableField("content")
    private String content;

    /**
     * 接收人ID（0表示所有人）
     */
    @TableField("to_id")
    private Long toId;

    /**
     * 发送人ID（0表示系统发送）
     */
    @TableField("from_id")
    private Long fromId;

    /**
     * 接收者类型（1-老师，2-学生）
     */
    @TableField("to_type")
    private Integer toType;

    /**
     * 发送者类型（0-系统，1-老师，2-学生）
     */
    @TableField("from_type")
    private Integer fromType;

    /**
     * 发送时间
     */
    @TableField("send_time")
    private LocalDateTime sendTime;

    /**
     * 创建时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 创建者ID
     */
    @TableField("creator")
    private Long creator;

    /**
     * 删除标记（0-未删除，1-已删除）
     */
    @TableLogic
    @TableField("deleted")
    private Integer deleted;
}
