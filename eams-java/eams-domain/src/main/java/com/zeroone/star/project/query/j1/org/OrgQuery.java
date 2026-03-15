package com.zeroone.star.project.query.j1.org;

import io.swagger.v3.oas.annotations.media.Schema;
import lombok.Data;

/**
 * 机构查询对象
 */
@Data
@Schema(description = "机构查询参数")
public class OrgQuery {

    @Schema(description = "机构ID", example = "1001")
    private Long orgId;

    @Schema(description = "机构名称（模糊查询）", example = "零壹教育")
    private String orgName;

    @Schema(description = "父机构ID（查询子机构）", example = "1000")
    private Long parentOrgId;

    @Schema(description = "机构状态（0-禁用 1-启用）", example = "1")
    private Integer status;

    @Schema(description = "机构类型（1-总校 2-分校 3-校区）", example = "2")
    private Integer orgType;
}