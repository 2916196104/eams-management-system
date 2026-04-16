package com.zeroone.star.project.query.j9.operation;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * 描述：试听卡查询对象
 * @author paopao
 * @version 1.0.0
 */
@EqualsAndHashCode(callSuper = true)
@Data
@ApiModel("试听卡查询对象")
public class CourseTrialQuery extends PageQuery {

    @ApiModelProperty(value = "课程ID", example = "1")
    private Long courseId;

    @ApiModelProperty(value = "试听卡名称", example = "暑期试听卡")
    private String title;

    @ApiModelProperty(value = "启用状态 1-启用 0-禁用", example = "1")
    private Integer state;
}
