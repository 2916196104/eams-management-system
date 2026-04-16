package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;

/**
 * <p>
 * 系统设置表（通知）
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("setting_notice")
public class SettingNotice implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
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
    private Integer wxOn;

    /**
     * 微信模板
     */
    private String wxCode;

    /**
     * 短信是否开启
     */
    private Integer smsOn;

    /**
     * 短信模板
     */
    private String smsCode;

    /**
     * Email 是否开启
     */
    private Integer emailOn;

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
