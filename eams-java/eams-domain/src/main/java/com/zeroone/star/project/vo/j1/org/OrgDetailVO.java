package com.zeroone.star.project.vo.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 机构详情VO（用于查看机构完整信息）
 */
@Data
@ApiModel(value = "机构详情返回数据")
public class OrgDetailVO {

    @ApiModelProperty(value = "机构ID", example = "1001")
    private Long orgId;

    @ApiModelProperty(value = "机构名称", example = "零壹教育海淀分校")
    private String orgName;

    @ApiModelProperty(value = "机构级别（1-集团 2-分校 3-部门）", example = "2")
    private Integer orgType;

    @ApiModelProperty(value = "机构级别描述", example = "分校")
    private String orgTypeDesc;

    @ApiModelProperty(value = "简称", example = "海淀分校")
    private String orgShortName;

    @ApiModelProperty(value = "营业执照", example = "91110108MA01XXXXX")
    private String businessLicense;

    @ApiModelProperty(value = "联系人", example = "王经理")
    private String contact;

    @ApiModelProperty(value = "地区", example = "北京市海淀区")
    private String region;

    @ApiModelProperty(value = "电话", example = "13800138000")
    private String phone;

    @ApiModelProperty(value = "传真", example = "010-12345678")
    private String fax;

    @ApiModelProperty(value = "邮箱", example = "contact@example.com")
    private String email;

    @ApiModelProperty(value = "排序号", example = "1")
    private Integer sortOrder;

    @ApiModelProperty(value = "状态（0-禁用 1-启用）", example = "1")
    private Integer status;

    @ApiModelProperty(value = "状态描述", example = "启用")
    private String statusDesc;

    @ApiModelProperty(value = "说明", example = "2026年新成立分校")
    private String remark;

    @ApiModelProperty(value = "父机构ID", example = "1000")
    private Long parentOrgId;

    @ApiModelProperty(value = "父机构名称", example = "零壹教育集团")
    private String parentOrgName;
}
