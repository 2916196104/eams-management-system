package com.zeroone.star.sys.entity.template;

import com.baomidou.mybatisplus.annotation.*;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

import java.time.LocalDateTime;

/**
 * 通知设置实体类
 * 对应数据库表 setting_notice
 *
 * @author isme
 * @since 2026-03-22
 */
@Data
@EqualsAndHashCode(callSuper = false)
@TableName("setting_notice")
@ApiModel(value = "SettingNotice数据对象", description = "模版表")
public class SettingNotice {

    @ApiModelProperty(value = "主键ID")
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    @ApiModelProperty(value = "名称")
    private String name;

    @ApiModelProperty(value = "编码")
    @TableField(value = "code")
    private String code;

    @ApiModelProperty(value = "微信是否开启", example = "0")
    @TableField("wx_on")
    private Integer wxOn = 0;  // 默认关闭

    @ApiModelProperty(value = "微信模板ID")
    @TableField("wx_code")
    private String wxCode;

    @ApiModelProperty(value = "短信是否开启", example = "0")
    @TableField("sms_on")
    private Integer smsOn = 0;  // 默认关闭

    @ApiModelProperty(value = "短信模板ID")
    @TableField("sms_code")
    private String smsCode;

    @ApiModelProperty(value = "邮件是否开启", example = "0")
    @TableField("email_on")
    private Integer emailOn;  // 数据库默认 NULL

    @ApiModelProperty(value = "说明信息")
    private String info;

    @ApiModelProperty(value = "排序号", example = "0")
    @TableField("sort_num")
    private Integer sortNum = 0;  // 默认排序0

    @ApiModelProperty(value = "分组编码")
    @TableField("group_code")
    private String groupCode;

    @ApiModelProperty(value = "参数说明")
    private String params;

    @ApiModelProperty(value = "消息备注信息")
    @TableField("notice_remark")
    private String noticeRemark;
}
