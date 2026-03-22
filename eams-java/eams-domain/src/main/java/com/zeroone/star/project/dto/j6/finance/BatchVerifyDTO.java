package com.zeroone.star.project.dto.j6.finance;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.util.List;

/**
 * 批量通过，批量驳回时添加的
 */
@Data
@ApiModel("批量驳回，批量通过数据对象")
public class BatchVerifyDTO {
    @ApiModelProperty(value = "请款记录ID列表", example = "[1001,1002,1003]", required = true)
    private List<Long> ids;

    @ApiModelProperty(value = "审核状态:1-通过,2-驳回", example = "1", required = true)
    private Integer verifyState;

    @ApiModelProperty(value = "审核备注(驳回时必填)", example = "请补充请款材料", required = false)
    private String verifyRemark;
}
