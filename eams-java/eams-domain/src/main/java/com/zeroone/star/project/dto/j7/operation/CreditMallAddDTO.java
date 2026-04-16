package com.zeroone.star.project.dto.j7.operation;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

/**
 * 运营界面里积分礼品管理的新增礼品类
 */

@Data
@ApiModel("礼品新增对象")
public class CreditMallAddDTO {
    @ApiModelProperty(value = "礼品名称", example = "电脑", required = true)
    @NotBlank(message = "礼品名称不能为空")
    private String name;
    @ApiModelProperty(value = "物料id", example = "1", required = true)
    @NotNull(message = "请选择物料")
    private Long materialId;
    @ApiModelProperty(value = "分类id", example = "1", required = true)
    @NotNull(message = "请选择分类")
    private Long categoryId;
    @ApiModelProperty(value = "兑换积分", example = "100", required = true)
    private Integer credit;
    @ApiModelProperty(value = "礼品说明", example = "搭载全新 Apple M3 芯片...")
    private String content;
    @ApiModelProperty(value = "图片", example = "/group1/M00/00/00/oYYBAGm1mq-AdjhgAAIPhi1s5Ww279.png")
    private String cover;

}
