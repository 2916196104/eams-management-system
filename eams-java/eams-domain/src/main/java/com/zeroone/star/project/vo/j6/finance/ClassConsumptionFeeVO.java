package com.zeroone.star.project.vo.j6.finance;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.math.BigDecimal;

/**
 * 消课课酬导出对象
 */
@Data
@ApiModel("消课课酬导出对象")
public class ClassConsumptionFeeVO {

    @ApiModelProperty(value = "老师姓名", example = "张三")
    private String teacherName;

    @ApiModelProperty(value = "月份（yyyy-MM）", example = "2026-01")
    private String month;

    @ApiModelProperty(value = "课程名称", example = "Java基础")
    private String courseName;

    @ApiModelProperty(value = "消课数", example = "2")
    private Integer consumptionCount;

    @ApiModelProperty(value = "消课课酬小计", example = "100.00")
    private BigDecimal feeSubtotal;


}
