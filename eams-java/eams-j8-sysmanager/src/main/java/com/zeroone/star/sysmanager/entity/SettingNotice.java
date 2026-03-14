package com.zeroone.star.sysmanager.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 系统设置表
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Getter
@Setter
@TableName("setting_notice")
public class SettingNotice implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 名称
     */
    private String name;

    /**
     * 码
     */
    private String code;

    /**
     * 微信是否开启
     */
    private Boolean wxOn;

    /**
     * 微信模板
     */
    private String wxCode;

    /**
     * 短信是否开启
     */
    private Boolean smsOn;

    /**
     * 短信模板
     */
    private String smsCode;

    /**
     * Email是否开启
     */
    private Boolean emailOn;

    /**
     * 说明
     */
    private String info;

    /**
     * 排序
     */
    private Integer sortNum;

    /**
     * 分组
     */
    private String groupCode;

    /**
     * 参数说明
     */
    private String params;

    /**
     * 消息备注信息
     */
    private String noticeRemark;


}
