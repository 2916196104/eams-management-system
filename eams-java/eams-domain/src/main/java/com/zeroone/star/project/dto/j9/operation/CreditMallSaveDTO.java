package com.zeroone.star.project.dto.j9.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

/**
 * 积分商城礼品新增/修改参数 DTO
 */
@Data
@ApiModel(description = "积分商城礼品新增/修改参数")
public class CreditMallSaveDTO {

    @ApiModelProperty(value = "礼品ID（修改时必填，新增时不传）", example = "1001")
    private Long id;

    @NotBlank(message = "礼品名称不能为空")
    @ApiModelProperty(value = "礼品名称", required = true, example = "校园定制U盘64G")
    private String name;

    @NotNull(message = "物料分类不能为空")
    @ApiModelProperty(value = "物料分类ID", required = true, example = "101")
    private Long materialId;

    @NotNull(message = "所属分类不能为空")
    @ApiModelProperty(value = "礼品分类ID", required = true, example = "10101")
    private Long categoryId;

    @NotNull(message = "兑换积分不能为空")
    @ApiModelProperty(value = "兑换所需积分", required = true, example = "800")
    private Integer credit;

    @ApiModelProperty(value = "礼品说明", example = "校园定制款64G高速U盘，防水抗震，印校徽")
    private String content;

    @ApiModelProperty(value = "礼品封面图片URL", example = "https://example.com/cover/usb64g.jpg")
    private String cover;
}
