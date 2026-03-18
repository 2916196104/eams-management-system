package com.zeroone.star.project.vo.j1.org;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.Date;

/**
 * 机构列表VO（符合VO命名规约，用于前端列表展示）
 */
@Data
@ApiModel(value="机构列表返回数据")
public class OrgListVO {

    @ApiModelProperty(value="机构ID", example = "1001")
    private Long orgId;

    @ApiModelProperty(value="机构名称", example = "零壹教育海淀分校")
    private String orgName;

    @ApiModelProperty(value="机构编码", example = "LD-HD-001")
    private String orgCode;

    @ApiModelProperty(value="父机构ID", example = "1000")
    private Long parentOrgId;

    @ApiModelProperty(value="父机构名称", example = "零壹教育总校")
    private String parentOrgName;

    @ApiModelProperty(value="机构类型（1-总校 2-分校 3-校区）", example = "2")
    private Integer orgType;

    @ApiModelProperty(value="机构类型描述", example = "分校")
    private String orgTypeDesc;

    @ApiModelProperty(value="联系人", example = "王经理")
    private String contact;

    @ApiModelProperty(value="联系电话", example = "13800138000")
    private String phone;

    @ApiModelProperty(value="机构状态（0-禁用 1-启用）", example = "1")
    private Integer status;

    @ApiModelProperty(value="机构状态描述", example = "启用")
    private String statusDesc;

    @ApiModelProperty(value="创建时间", example = "2026-03-15 10:00:00")
    private Date createTime;

    @ApiModelProperty(value="修改时间", example = "2026-03-15 11:00:00")
    private Date updateTime;
}