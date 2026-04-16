package com.zeroone.star.project.vo.j6.finance;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * 月课时费导出对象
 */
@Data
@ApiModel("月课时费导出对象")
public class MonthlyClassFeeVO {


    /**
     * 姓名
     */
    @ApiModelProperty(value = "姓名")
    private String teacherName;

    /**
     * 月份（格式：yyyy-MM）
     */
    @ApiModelProperty(value = "月份")
    private String month;

    /**
     * 单节上课费（元/节）
     */
    @ApiModelProperty(value = "单节上课费")
    private BigDecimal singleClassFee;

    /**
     * 上课课次数
     */
    @ApiModelProperty(value = "上课课次数")
    private Integer classCount;

    /**
     * 上课费小计
     */
    @ApiModelProperty(value = "上课费小计")
    private BigDecimal classFeeSubtotal;

    /**
     * 单节助教费（元/节）
     */
    @ApiModelProperty(value = "单节助教费")
    private BigDecimal singleAssistantFee;

    /**
     * 助教课次数
     */
    @ApiModelProperty(value = "助教课次数")
    private Integer assistantCount;

    /**
     * 助教费小计
     */
    @ApiModelProperty(value = "助教费小计")
    private BigDecimal assistantFeeSubtotal;

}
