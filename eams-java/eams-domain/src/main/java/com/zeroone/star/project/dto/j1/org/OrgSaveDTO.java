package com.zeroone.star.project.dto.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

/**
 * 机构保存DTO（用于添加子机构、编辑机构）
 */
@Data
@ApiModel(value = "机构保存请求数据")
public class OrgSaveDTO {

    @ApiModelProperty(value = "机构ID（新增不传，修改时必传）", example = "1001")
    private Long orgId;

    @NotBlank(message = "机构名称不能为空")
    @ApiModelProperty(value = "机构名称", required = true, example = "零壹教育海淀分校")
    private String orgName;

    @NotNull(message = "父机构ID不能为空")
    @ApiModelProperty(value = "父机构ID（顶级机构传0）", required = true, example = "0")
    private Long parentOrgId;

    @NotNull(message = "机构级别不能为空")
    @ApiModelProperty(value = "机构级别（1-集团 2-分校 3-部门）", required = true, example = "2")
    private Integer orgType;

    @ApiModelProperty(value = "简称", example = "海淀分校")
    private String orgShortName;

    @ApiModelProperty(value = "联系人", example = "王经理")
    private String contact;

    @ApiModelProperty(value = "电话", example = "13800138000")
    private String phone;

    @ApiModelProperty(value = "传真", example = "010-12345678")
    private String fax;

    @ApiModelProperty(value = "邮箱", example = "contact@example.com")
    private String email;

    @ApiModelProperty(value = "排序号", example = "1")
    private Integer sortOrder;

    @ApiModelProperty(value = "状态（0-禁用 1-启用）", example = "1")
    private Integer status = 1;

    @ApiModelProperty(value = "说明", example = "2026年新成立分校")
    private String remark;
}
