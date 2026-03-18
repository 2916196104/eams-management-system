package com.zeroone.star.project.dto.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

/**
 * 机构保存DTO
 */
@Data
@ApiModel(value = "机构保存请求数据")
public class OrgSaveDTO {

    @ApiModelProperty(value = "机构ID（新增不传，修改传）", example = "1001")
    private Long orgId;

    @NotBlank(message = "机构名称不能为空")
    @ApiModelProperty(value = "机构名称", required = true, example = "零壹教育海淀分校")
    private String orgName;

    @NotNull(message = "父机构ID不能为空")
    @ApiModelProperty(value = "父机构ID", required = true, example = "1000")
    private Long parentOrgId;

    @ApiModelProperty(value = "机构编码", example = "LD-HD-001")
    private String orgCode;

    @NotNull(message = "机构类型不能为空")
    @ApiModelProperty(value = "机构类型（1-总校 2-分校 3-校区）", required = true, example = "2")
    private Integer orgType;

    @ApiModelProperty(value = "联系人", example = "阿伟经理")
    private String contact;

    @ApiModelProperty(value = "联系电话", example = "13800138000")
    private String phone;

    @ApiModelProperty(value = "地址", example = "北京市海淀区XX路XX号")
    private String address;

    @ApiModelProperty(value = "备注", example = "2026年新成立分校")
    private String remark;

    @ApiModelProperty(value = "机构状态（0-禁用 1-启用）", example = "1")
    private Integer status = 1; // 默认启用
}