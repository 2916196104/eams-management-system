package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 站内信
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("message")
public class Message implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 发送标题
     */
    private String title;

    /**
     * 发送内容
     */
    private String content;

    /**
     * 接收人 ID 0 所有
     */
    private Long toId;

    /**
     * 发送人 ID
     */
    private Long fromId;

    /**
     * 接受者类型  1 老师 2 学生
     */
    private Integer toType;

    /**
     * 发送者类型 0 系统 1 老师 2 学生
     */
    private Integer fromType;

    /**
     * 发送时间
     */
    private LocalDateTime sendTime;

    /**
     * 创建时间
     */
    private LocalDateTime addTime;

    /**
     * 创建者
     */
    private Long creator;

    /**
     * 删除标记
     */
    private Integer deleted;
}
