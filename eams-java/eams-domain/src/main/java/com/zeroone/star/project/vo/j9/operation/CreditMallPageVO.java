package com.zeroone.star.project.vo.j9.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.Date;

/**
 * 积分商城礼品分页列表 VO
 */
@Data
@ApiModel(description = "积分商城礼品分页列表VO")
public class CreditMallPageVO {

    @ApiModelProperty(value = "礼品ID", example = "1001")
    private Long id;

    @ApiModelProperty(value = "礼品封面图片URL", example = "https://example.com/cover/usb64g.jpg")
    private String cover;

    @ApiModelProperty(value = "礼品名称", example = "校园定制U盘64G")
    private String name;

    @ApiModelProperty(value = "所属学校名称", example = "XX大学")
    private String schoolName;

    @ApiModelProperty(value = "兑换所需积分", example = "800")
    private Integer credit;

    @ApiModelProperty(value = "已兑换数量", example = "126")
    private Integer saleNum;

    @ApiModelProperty(value = "浏览次数", example = "892")
    private Integer viewNum;

    @ApiModelProperty(value = "最后编辑时间", example = "2026-02-15 14:10:20")
    private Date editTime;

    @ApiModelProperty(value = "是否可兑换（1-启用，0-禁用）", example = "1")
    private Integer state;
}
