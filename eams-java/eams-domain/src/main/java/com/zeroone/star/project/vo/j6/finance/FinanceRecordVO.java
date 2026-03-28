package com.zeroone.star.project.vo.j6.finance;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * 财务记录表
 */
@Data
@ApiModel("财务记录数据对象")
public class FinanceRecordVO {
    @ApiModelProperty(value = "财务记录id",example = "123456789")
    private Long id;

    @ApiModelProperty("款项类型")
    private Integer type;

    @ApiModelProperty(value = "标题",required = true,example = "样例标题")
    private String title;

    @ApiModelProperty(value = "金额,退款为负数",required = true,example = "10000")
    private BigDecimal amount;

    @ApiModelProperty(value = "付款人id",required = true,example = "1234")
    private Long payer;

    @ApiModelProperty(value = "学生姓名",required = true,example = "张三")
    private String studentName;

    @ApiModelProperty(value = "经办人id",required = true,example = "1145")
    private Long operator;

    @ApiModelProperty(value = "经手人姓名",required = true,example = "李四")
    private String operatorName;

    @ApiModelProperty(value = "款项备注")
    private String remark;

    @ApiModelProperty(value = "认款状态",required = true,example = "0")
    private Integer verifyState;

    @ApiModelProperty(value = "认款信息")
    private String verifyRemark;

    @ApiModelProperty("提交时间")
    private LocalDateTime submitTime;
}
