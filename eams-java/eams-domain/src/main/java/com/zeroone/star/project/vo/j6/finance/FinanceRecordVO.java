package com.zeroone.star.project.vo.j6.finance;

import com.alibaba.excel.annotation.ExcelProperty;
import com.alibaba.excel.annotation.format.DateTimeFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * Finance record export object.
 */
@Data
@ApiModel("Finance record object")
public class FinanceRecordVO {
    @ExcelProperty("\u8d22\u52a1\u8bb0\u5f55ID")
    @ApiModelProperty(value = "Finance record id", example = "123456789")
    private Long id;

    @ExcelProperty("\u6b3e\u9879\u7c7b\u578b")
    @ApiModelProperty("Fund item type")
    private Integer type;

    @ExcelProperty("\u6807\u9898")
    @ApiModelProperty(value = "Title", required = true, example = "Example")
    private String title;

    @ExcelProperty("\u91d1\u989d")
    @ApiModelProperty(value = "Amount", required = true, example = "10000")
    private BigDecimal amount;

    @ExcelProperty("\u4ed8\u6b3e\u4eba")
    @ApiModelProperty(value = "Payer name", example = "Zhang San")
    private String studentName;

    @ExcelProperty("\u7ecf\u529e\u4ebaID")
    @ApiModelProperty(value = "Operator id", example = "1145")
    private Long operator;

    @ExcelProperty("\u6b3e\u9879\u5907\u6ce8")
    @ApiModelProperty(value = "Remark")
    private String remark;

    @ExcelProperty("\u8ba4\u6b3e\u72b6\u6001")
    @ApiModelProperty(value = "Verify state", example = "0")
    private Integer verifyState;

    @ExcelProperty("\u8ba4\u6b3e\u4fe1\u606f")
    @ApiModelProperty(value = "Verify remark")
    private String verifyRemark;

    @ExcelProperty("\u63d0\u4ea4\u65f6\u95f4")
    @DateTimeFormat("yyyy-MM-dd HH:mm:ss")
    @ApiModelProperty("Submit time")
    private LocalDateTime submitTime;
}