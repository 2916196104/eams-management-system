package com.zeroone.star.project.query.j6.finance;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;

/**
 * 款项列表查询条件构造
 */
@Data
@ApiModel("款项信息查询条件")
public class FinanceRecordQuery extends PageQuery {
    @ApiModelProperty(value = "标题",example = "样例标题")
    private String title;

    @ApiModelProperty(value = "经手人",example = "张三")
    private String handlerName;

    @ApiModelProperty(value = "付款人",example = "李四")
    private String payerName;

    @ApiModelProperty(value = "认款状态,0：审核中 1：已审核 2：已拒绝",example = "0")
    private Integer verifyState;

    @ApiModelProperty(value = "类型",example = "0")
    private Integer itemType;

}
