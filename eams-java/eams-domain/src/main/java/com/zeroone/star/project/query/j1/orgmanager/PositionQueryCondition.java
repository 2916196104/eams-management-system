package com.zeroone.star.project.query.j1.orgmanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.Min;

/**
 * <p>
 * 描述：职位列表查询条件
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
@Data
@ApiModel("职位列表查询条件")
public class PositionQueryCondition {
    @Min(value = 1, message = "页码最小值为1")
    @ApiModelProperty(value = "页码", example = "1")
    private Integer page = 1;

    @Min(value = 1, message = "每页条数最小值为1")
    @ApiModelProperty(value = "每页条数", example = "30")
    private Integer pageSize = 30;

    @ApiModelProperty(value = "职位名称，支持模糊搜索", example = "校长")
    private String name = "";
}
