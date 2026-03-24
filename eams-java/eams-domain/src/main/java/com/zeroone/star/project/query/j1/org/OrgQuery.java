package com.zeroone.star.project.query.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 机构查询条件
 */
@Data
@ApiModel(value = "机构查询条件")
public class OrgQuery {

    @ApiModelProperty(value = "机构名称（模糊查询）", example = "海淀")
    private String orgName;

    @ApiModelProperty(value = "父机构ID（查询子机构时传）", example = "1000")
    private Long parentOrgId;

    @ApiModelProperty(value = "机构级别（1-集团 2-分校 3-部门）", example = "2")
    private Integer orgType;

    @ApiModelProperty(value = "状态（0-禁用 1-启用）", example = "1")
    private Integer status;
}
