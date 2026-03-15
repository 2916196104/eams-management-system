package com.zeroone.star.project.vo.j1.org;


import io.swagger.v3.oas.annotations.media.Schema;
import lombok.Data;

import java.util.List;

/**
 * 机构名称树VO（用于前端树形展示机构层级）
 */
@Data
@Schema(description = "机构名称树返回数据")
public class OrgTreeVO {

    @Schema(description = "机构ID", example = "1001")
    private Long orgId;

    @Schema(description = "机构名称", example = "零壹教育海淀分校")
    private String orgName;

    @Schema(description = "父机构ID", example = "1000")
    private Long parentOrgId;

    @Schema(description = "子机构列表")
    private List<OrgTreeVO> children;
}