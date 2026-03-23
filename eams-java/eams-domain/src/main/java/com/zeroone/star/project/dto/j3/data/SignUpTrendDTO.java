package com.zeroone.star.project.dto.j3.data;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

/**
 * 报名趋势传输对象
 */
@ApiModel("报名趋势传输对象")
@Data
public class SignUpTrendDTO {
    /**
     * 总课程数
     */
    @ApiModelProperty(value = "总课程数", example = "15")
    private Double countLessonTotal;
    /**
     * 全部收入
     */
    @ApiModelProperty(value = "全部收入", example = "1222.05")
    private BigDecimal totalAmount;
    /**
     * 报名数
     */
    @ApiModelProperty(value = "报名数", example = "1")
    private Integer totalCount;
    /**
     * 报名日期
     */
    @ApiModelProperty(value = "日期", example = "03-10")
    private String dates;
}
