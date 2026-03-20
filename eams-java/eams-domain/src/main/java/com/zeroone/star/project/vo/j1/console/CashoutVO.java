package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.List;

@Data
@ApiModel(value = "CashoutVO", description = "请款列表视图对象")
public class CashoutVO {

    @ApiModelProperty(value = "总记录数")
    private Long total;

    @ApiModelProperty(value = "请款列表")
    private List<CashoutItem> list;

    @Data
    @ApiModel(value = "CashoutItem", description = "单条请款记录")
    public static class CashoutItem {

        @ApiModelProperty(value = "主键ID")
        private Long id;

        @ApiModelProperty(value = "请款项目")
        private String title;

        @ApiModelProperty(value = "款项类型")
        private String typeName;

        @ApiModelProperty(value = "申请人")
        private String applicantName;

        @ApiModelProperty(value = "收款人")
        private String payeeName;

        @ApiModelProperty(value = "请款金额")
        private BigDecimal amount;

        @ApiModelProperty(value = "申请时间")
        private LocalDateTime applyTime;

        @ApiModelProperty(value = "收款账号")
        private String account;

        @ApiModelProperty(value = "请款说明")
        private String info;

        @ApiModelProperty(value = "审核状态")
        private String verifyStateName;

        @ApiModelProperty(value = "审核信息")
        private String verifyInfo;
    }
}
