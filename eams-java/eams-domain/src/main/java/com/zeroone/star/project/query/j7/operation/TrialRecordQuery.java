package com.zeroone.star.project.query.j7.operation;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

import javax.validation.constraints.NotNull;


@EqualsAndHashCode(callSuper = true)
@Data
@ApiModel("试听卡领取记录查询对象")
public class TrialRecordQuery extends PageQuery {
    @ApiModelProperty(value = "试听卡ID(必传）", example = "1")
    @NotNull(message = "试听卡ID不能为空")
    private Long trialId;

    @ApiModelProperty(value = "学生ID", example = "1")
    private Long studentId;
}
