package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
@ApiModel(value = "CashoutVO", description = "请款信息视图对象")
public class CashoutVO {

    @ApiModelProperty(value = "主键ID")
    private Long id;

    @ApiModelProperty(value = "请款项目名")
    private String title;

    @ApiModelProperty(value = "请款类型")
    private Integer type;

    @ApiModelProperty(value = "请款金额")
    private BigDecimal amount;

    @ApiModelProperty(value = "收款人")
    private String payeeName;

    @ApiModelProperty(value = "收款账号")
    private String account;

    @ApiModelProperty(value = "请款信息")
    private String info;

    @ApiModelProperty(value = "审批状态")
    private Integer verifyState;

    @ApiModelProperty(value = "审核人")
    private Long verifyStaff;

    @ApiModelProperty(value = "审核时间")
    private LocalDateTime verifyTime;

    @ApiModelProperty(value = "审核备注")
    private String verifyRemark;

    @ApiModelProperty(value = "申请人")
    private Long creator;

    @ApiModelProperty(value = "编辑人")
    private Long editor;

    @ApiModelProperty(value = "添加时间")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "编辑时间")
    private LocalDateTime editTime;

    @ApiModelProperty(value = "删除标记")
    private Boolean deleted;

    @ApiModelProperty(value = "附件id列表")
    private String attachFile;

    @ApiModelProperty(value = "创建者所属组织ID")
    private Long orgId;
}
