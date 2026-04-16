package com.zeroone.star.project.query.j9.operation;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

/**
 * 积分商城礼品分页查询参数
 */
@Getter
@Setter
@ToString
@ApiModel(value = "CreditMallPageQuery", description = "积分商城礼品分页查询参数")
public class CreditMallPageQuery extends PageQuery {

    @ApiModelProperty(value = "礼品名称（可选，模糊匹配）", example = "鼠标")
    private String name;

    @ApiModelProperty(value = "是否可兑换（可选，1-是，0-否）", example = "1")
    private Integer state;
}
