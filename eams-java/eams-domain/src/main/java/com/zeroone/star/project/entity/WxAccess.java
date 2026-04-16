package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 微信登录记录表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("wx_access")
public class WxAccess implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 微信 openid
     */
    private String openid;

    /**
     * 微信 unionid
     */
    private String unionid;

    /**
     * 昵称
     */
    private String nickname;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;

    /**
     * 最后登录时间
     */
    private LocalDateTime latestLogin;

    /**
     * 是否取消关注
     */
    private Integer unsubscribe;

    /**
     * 头像
     */
    private String headImg;

    /**
     * 取消关注事件
     */
    private LocalDateTime unsubTime;

    /**
     * 性别
     */
    private Integer gender;

    /**
     * 城市
     */
    private String city;

    /**
     * 省份
     */
    private String province;

    /**
     * 国家
     */
    private String country;

    /**
     * 通过什么注册的 mp 公众号 miniapp 小程序
     */
    private String regFrom;
}
