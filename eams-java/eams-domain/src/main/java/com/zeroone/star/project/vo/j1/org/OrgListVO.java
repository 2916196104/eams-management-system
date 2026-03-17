package com.zeroone.star.project.vo.j1.org;


import io.swagger.v3.oas.annotations.media.Schema;
import lombok.Data;

import java.util.Date;

/**
 * 机构列表VO（符合VO命名规约，用于前端列表展示）
 */
@Data
@Schema(description = "机构列表返回数据")
public class OrgListVO {

    @Schema(description = "机构ID", example = "1001")
    private Long orgId;

    @Schema(description = "机构名称", example = "零壹教育海淀分校")
    private String orgName;

    @Schema(description = "机构编码", example = "LD-HD-001")
    private String orgCode;

    @Schema(description = "父机构ID", example = "1000")
    private Long parentOrgId;

    @Schema(description = "父机构名称", example = "零壹教育总校")
    private String parentOrgName;

    @Schema(description = "机构类型（1-总校 2-分校 3-校区）", example = "2")
    private Integer orgType;

    @Schema(description = "机构类型描述", example = "分校")
    private String orgTypeDesc;

    @Schema(description = "联系人", example = "王经理")
    private String contact;

    @Schema(description = "联系电话", example = "13800138000")
    private String phone;

    @Schema(description = "机构状态（0-禁用 1-启用）", example = "1")
    private Integer status;

    @Schema(description = "机构状态描述", example = "启用")
    private String statusDesc;

    @Schema(description = "创建时间", example = "2026-03-15 10:00:00")
    private Date createTime;

    @Schema(description = "修改时间", example = "2026-03-15 11:00:00")
    private Date updateTime;
}