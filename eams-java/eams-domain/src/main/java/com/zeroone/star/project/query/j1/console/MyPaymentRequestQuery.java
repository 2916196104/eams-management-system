package com.zeroone.star.project.query.j1.console;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@ApiModel(value = "MyPaymentRequestQuery", description = "Cashout query")
public class MyPaymentRequestQuery extends PageQuery {

    @ApiModelProperty(value = "Apply time start")
    private LocalDateTime addTimeStart;

    @ApiModelProperty(value = "Apply time end")
    private LocalDateTime addTimeEnd;

    @ApiModelProperty(value = "Verify state")
    private Integer verifyState;
}
