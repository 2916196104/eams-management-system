package com.zeroone.star.project.query.j7.interaction;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel(value = "作业查询条件")
public class HomeworkQuery extends PageQuery {
    @ApiModelProperty(value = "班级ID")
    private Long classId;

    @ApiModelProperty(value = "作业标题（模糊查询）")
    private String title;

    @ApiModelProperty(value = "创建人ID")
    private Long creator;

    @ApiModelProperty(value = "组织ID")
    private Long orgId;
}