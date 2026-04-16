package com.zeroone.star.project.dto.j7.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("礼品详情对象")
public class CreditMallDetailDTO {
    @ApiModelProperty("礼品名称")
    private String name;

    @ApiModelProperty("图片")
    private String cover;

    @ApiModelProperty("物料名称")
    private String materialName;

    @ApiModelProperty("分类名称")
    private String categoryName;

    @ApiModelProperty("兑换积分")
    private Integer credit;

    @ApiModelProperty("礼品说明")
    private String content;
}
