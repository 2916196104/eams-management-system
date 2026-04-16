package com.zeroone.star.project.vo.j9.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * 批量审核结果 VO
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(description = "批量审核结果")
public class CreditExchangeBatchAuditVO {

    @ApiModelProperty(value = "是否全部审核成功", example = "true")
    private Boolean allSuccess;

    @ApiModelProperty(value = "成功审核的数量", example = "3")
    private Integer successCount;

    @ApiModelProperty(value = "失败的数量（可选）", example = "0")
    private Integer failCount;
}