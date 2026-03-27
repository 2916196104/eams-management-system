package com.zeroone.star.project.vo.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 机构列表VO（用于前端列表展示，仅包含关键字段）
 */
@Data
@ApiModel(value = "机构列表返回数据")
public class OrgListVO {

    @ApiModelProperty(value = "机构ID（唯一标识）", example = "1001")
    private Long orgId;

    @ApiModelProperty(value = "机构名称", example = "零壹教育海淀分校")
    private String orgName;

    @ApiModelProperty(value = "全称", example = "北京零壹教育科技有限公司海淀分公司")
    private String orgFullName;

    @ApiModelProperty(value = "机构级别（1-集团 2-分校 3-部门）", example = "2")
    private Integer orgType;

    @ApiModelProperty(value = "机构级别描述", example = "分校")
    private String orgTypeDesc;

    @ApiModelProperty(value = "联系人", example = "王经理")
    private String contact;

    @ApiModelProperty(value = "电话", example = "13800138000")
    private String phone;

    @ApiModelProperty(value = "父机构ID（用于判断是否有子节点）", example = "1000")
    private Long parentOrgId;
}
