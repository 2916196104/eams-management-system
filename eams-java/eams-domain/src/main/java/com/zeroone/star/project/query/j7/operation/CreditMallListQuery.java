package com.zeroone.star.project.query.j7.operation;


import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 描述：礼品列表查询对象
 */


@Data
@ApiModel("积分礼品列表查询对象")
public class CreditMallListQuery extends PageQuery {
    @ApiModelProperty(value = "礼品名称", example = "电脑")
    private String name;
    @ApiModelProperty(value = "状态(是否可以兑换)", example = "1", allowableValues = "0,1")
    private Integer state;
}
