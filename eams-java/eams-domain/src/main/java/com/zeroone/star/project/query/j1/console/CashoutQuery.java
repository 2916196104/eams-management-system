package com.zeroone.star.project.query.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@ApiModel(value = "CashoutQuery", description = "请款信息查询条件")
public class CashoutQuery {

    @ApiModelProperty(value = "申请时间开始")
    private LocalDateTime addTimeStart;

    @ApiModelProperty(value = "申请时间结束")
    private LocalDateTime addTimeEnd;

    @ApiModelProperty(value = "审核状态")
    private Integer verifyState;

    @ApiModelProperty(value = "当前页")
    private Integer pageNum = 1;

    @ApiModelProperty(value = "每页大小")
    private Integer pageSize = 30;
}
