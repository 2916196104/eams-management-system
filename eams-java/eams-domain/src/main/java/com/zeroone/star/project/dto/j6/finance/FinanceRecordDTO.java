package com.zeroone.star.project.dto.j6.finance;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@Data
public class FinanceRecordDTO {
    @ApiModelProperty(value = "财务记录id",example = "123456789")
    private Long id;

    @ApiModelProperty(value = "标题",required = true,example = "样例标题")
    private String title;

    @ApiModelProperty(value = "金额,退款为负数",required = true,example = "10000")
    private BigDecimal amount;

    @ApiModelProperty(value = "收入项类型",required = true,example = "0")
    private Integer itemType;

    @ApiModelProperty(value = "付款人id",required = true,example = "1")
    private Long payer;

    @ApiModelProperty(value = "学生姓名",required = true,example = "张三")
    private String studentName;

    @ApiModelProperty(value = "分校名称",required = true,example = "学校总部")
    private String schoolName;

    @ApiModelProperty(value = "学习阶段",required = true,example = "1")
    private Integer stage;

    @ApiModelProperty(value = "经办人id",required = true,example = "1145")
    private Long operator;

    @ApiModelProperty(value = "经办人姓名",required = true,example = "李四")
    private String handlerName;

    @ApiModelProperty(value = "员工职位",required = true,example = "教职工")
    private String position;

    @ApiModelProperty(value = "款项备注")
    private String remark;

    @ApiModelProperty(value = "审核确认状态,0：审核中 1：已审核 2：已拒绝",required = true,example = "0")
    private Integer verifyState;

    @ApiModelProperty(value = "审核备注")
    private String verifyRemark;
}
