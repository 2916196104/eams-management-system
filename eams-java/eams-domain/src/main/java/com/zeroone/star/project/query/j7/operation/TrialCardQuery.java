package com.zeroone.star.project.query.j7.operation;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

@EqualsAndHashCode(callSuper = true)
@Data
@ApiModel("试听卡列表查询对象")
public class TrialCardQuery extends PageQuery {
    @ApiModelProperty(value = "试听卡标题", example = "语文")
    private String title;

    @ApiModelProperty(value = "课程ID", example = "1")
    private Long courseId;

    @ApiModelProperty(value = "状态", example = "true")
    private Boolean state;
}
