package com.zeroone.star.sysmanager.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import io.swagger.annotations.ApiModelProperty;
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
@Data
@TableName("setting_notice")
public class SettingNotice implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @ApiModelProperty(value = "学员id", example = "1")
    private Long id;

    /**
     * 名称
     */
    @ApiModelProperty(value = "学员姓名", example = "1")
    private String name;

    /**
     * 码
     */
    @ApiModelProperty(value = "码", example = "1")
    private String code;

    /**
     * 微信是否开启
     */
    @ApiModelProperty(value = "微信是否开启", example = "true")
    private Boolean wxOn;

    /**
     * 微信模板
     */
    @ApiModelProperty(value = "微信模板", example = "1")
    private String wxCode;

    /**
     * 短信是否开启
     */
    @ApiModelProperty(value = "短信是否开启", example = "true")
    private Boolean smsOn;

    /**
     * 短信模板
     */
    @ApiModelProperty(value = "短信模板", example = "1")
    private String smsCode;

    /**
     * Email是否开启
     */
    @ApiModelProperty(value = "Email是否开启", example = "true")
    private Boolean emailOn;

    /**
     * 说明
     */
    @ApiModelProperty(value = "说明", example = "1")
    private String info;

    /**
     * 排序
     */
    @ApiModelProperty(value = "排序", example = "1")
    private Integer sortNum;

    /**
     * 分组
     */
    @ApiModelProperty(value = "分组", example = "1")
    private String groupCode;

    /**
     * 参数说明
     */
    @ApiModelProperty(value = "参数说明", example = "1")
    private String params;

    /**
     * 消息备注信息
     */
    @ApiModelProperty(value = "消息备注信息", example = "1")
    private String noticeRemark;


}
