package com.zeroone.star.project.dto.j6.finance;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * 财务记录表
 */
@Data
public class FinanceRecordDTO {
    @ApiModelProperty(value = "财务记录id",example = "123456789")
    private Long id;

    @ApiModelProperty(value = "款项类型",required = true,example = "0")
    private Integer itemType;

    @ApiModelProperty(value = "标题",required = true,example = "样例标题")
    private String title;

    @ApiModelProperty(value = "金额,退款为负数",required = true,example = "10000")
    private BigDecimal amount;

    @ApiModelProperty(value = "学员",required = true,example = "张三")
    private String studentName;

    @ApiModelProperty(value = "经手人",required = true,example = "李四")
    private String handlerName;

    @ApiModelProperty(value = "备注说明",example = "这是一个备注说明")
    private String remark;

    @ApiModelProperty(value = "提交时间",example = "2026-03-15")
    private LocalDateTime submitTime;

    @ApiModelProperty(value = "认款状态,0：审核中 1：已审核 2：已拒绝",required = true,example = "0")
    private Integer verifyState;

    @ApiModelProperty(value = "认款信息",example = "这是一个认款信息")
    private String verifyRemark;
}