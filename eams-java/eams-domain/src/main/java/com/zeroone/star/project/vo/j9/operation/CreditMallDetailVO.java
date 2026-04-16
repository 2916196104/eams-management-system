package com.zeroone.star.project.vo.j9.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 积分商城礼品详情 VO
 */
@Data
@ApiModel(description = "积分商城礼品详情VO")
public class CreditMallDetailVO {

    @ApiModelProperty(value = "礼品ID", example = "1001")
    private Long id;

    @ApiModelProperty(value = "礼品名称", example = "校园定制U盘64G")
    private String name;

    @ApiModelProperty(value = "物料分类ID", example = "101")
    private Long materialId;

    @ApiModelProperty(value = "礼品分类ID", example = "10101")
    private Long categoryId;

    @ApiModelProperty(value = "分类名称", example = "数码产品")
    private String categoryName;

    @ApiModelProperty(value = "兑换所需积分", example = "800")
    private Integer credit;

    @ApiModelProperty(value = "礼品说明", example = "校园定制款64G高速U盘，防水抗震，印校徽")
    private String content;

    @ApiModelProperty(value = "礼品封面图片URL", example = "https://example.com/cover/usb64g.jpg")
    private String cover;
}
