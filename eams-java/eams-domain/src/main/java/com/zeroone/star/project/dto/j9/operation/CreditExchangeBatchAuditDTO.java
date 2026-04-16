package com.zeroone.star.project.dto.j9.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
 * 批量审核兑换申请参数 DTO
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(description = "批量审核兑换申请参数")
public class CreditExchangeBatchAuditDTO {

    @NotEmpty(message = "至少选择一条兑换申请")
    @ApiModelProperty(value = "兑换申请ID列表", required = true, example = "[701,702,703]")
    private List<Long> ids;

    @NotNull(message = "审核状态不能为空")
    @ApiModelProperty(value = "审核状态（2=通过，3=驳回）", required = true, example = "2")
    private Integer verifyState;

    @ApiModelProperty(value = "审核说明（可选）", example = "批量通过符合条件的申请")
    private String verifyRemark;
}