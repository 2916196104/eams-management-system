package com.zeroone.star.project.query.j6.finance;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 消课课酬查询条件
 */
@Data
public class ClassConsumptionFeeQuery extends PageQuery {

    /*
    老师姓名，用来指定查询，不必须
     */
    @ApiModelProperty(value = "姓名", example = "张三")
    private String name;
    /*
    开始时间
     */
    @ApiModelProperty(value = "开始时间", example = "2023-01-01")
    private LocalDateTime startTime;
    /*
    结束时间
     */
    @ApiModelProperty(value = "结束时间", example = "2023-01-31")
    private LocalDateTime endTime;
}