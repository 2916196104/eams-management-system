package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 使用帮助
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("help")
public class Help implements Serializable {

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
     * 类型
     */
    private String type;

    /**
     * 创建者
     */
    private Long creator;

    /**
     * 创建时间
     */
    private LocalDateTime addTime;

    /**
     * 逻辑删除
     */
    private Integer deleted;

    /**
     * 编辑时间
     */
    private LocalDateTime editTime;

    /**
     * 编辑者
     */
    private Long editor;

    /**
     * 状态
     */
    private Integer state;

    /**
     * 排序
     */
    private Integer sortNum;
}
