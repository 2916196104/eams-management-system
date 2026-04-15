package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/**
 * Generic result for batch operations.
 */
@Data
@ApiModel(value = "BatchOperateResultVO", description = "Result summary for batch operations")
public class BatchOperateResultVO {

    @ApiModelProperty(value = "Total count")
    private Integer totalCount;

    @ApiModelProperty(value = "Success count")
    private Integer successCount;

    @ApiModelProperty(value = "Failed count")
    private Integer failedCount;

    @ApiModelProperty(value = "Failed ids")
    private List<Long> failedIds;
}
