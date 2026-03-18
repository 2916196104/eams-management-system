package com.zeroone.star.project.query.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 机构查询对象
 */
@Data
@ApiModel(value= "机构查询参数")
public class OrgQuery {

    @ApiModelProperty(value= "机构ID", example = "1001")
    private Long orgId;

    @ApiModelProperty(value= "机构名称（模糊查询）", example = "零壹教育")
    private String orgName;

    @ApiModelProperty(value= "父机构ID（查询子机构）", example = "1000")
    private Long parentOrgId;

    @ApiModelProperty(value= "机构状态（0-禁用 1-启用）", example = "1")
    private Integer status;

    @ApiModelProperty(value= "机构类型（1-总校 2-分校 3-校区）", example = "2")
    private Integer orgType;
}