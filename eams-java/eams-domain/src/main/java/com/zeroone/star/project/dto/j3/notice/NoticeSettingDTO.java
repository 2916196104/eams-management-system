package com.zeroone.star.project.dto.j3.notice;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class NoticeSettingDTO {


    @ApiModelProperty(value = "唯一标识", example = "1")
    private Long id;

    @ApiModelProperty(value = "邮件通知开关",example = "1",required = true)
    private boolean emailon;

    @ApiModelProperty(value = "微信通知开关",example = "1",required = true)
    private boolean wechaton;

    @ApiModelProperty(value = "微信消息模板id",example = "0XBiEnSV5fCLaDXdxguQvlurhWwwVVS_ijci0")
    private String noticewechatId;

    @ApiModelProperty(value = "短信通知",example = "1",required = true)
    private boolean messageon;

    @ApiModelProperty(value = "短信消息模板id",example = "0XBiEnSV5fCLaDXdxguQvlurhWwwVVS_ijci0")
    private String MessageId_eg;

    @ApiModelProperty(value = "提示信息",example = "0XBiEnSV5fCLaDXdxguQvlurhWwwVVS_ijci0")
    private String tips;


}
