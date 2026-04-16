package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 微信菜单设置
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("wx_menu")
public class WxMenu implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 不自增主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 上级 id
     */
    private Long pid;

    /**
     * 菜单名
     */
    private String name;

    /**
     * 菜单 URL
     */
    private String url;

    /**
     * 菜单类型
     */
    private String type;

    /**
     * 事件 KEY
     */
    private String keyCode;

    /**
     * 小程序 APPID
     */
    private String appid;

    /**
     * 小程序页面地址
     */
    private String pagepath;

    /**
     * 素材 media_id
     */
    private String mediaId;

    /**
     * 文章 article_id
     */
    private String articleId;

    /**
     * 发送文字
     */
    private String sendText;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 编辑时间
     */
    private LocalDateTime editTime;
}
