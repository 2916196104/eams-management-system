package com.zeroone.star.project.vo.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/**
 * 机构名称树VO（用于前端树形展示机构层级）
 */
@Data
@ApiModel(value = "机构名称树返回数据")
public class OrgTreeVO {

    @ApiModelProperty(value = "机构ID（唯一标识）", example = "1001")
    private Long orgId;

    @ApiModelProperty(value = "机构名称", example = "零壹教育海淀分校")
    private String orgName;

    @ApiModelProperty(value = "父机构ID", example = "1000")
    private Long parentOrgId;

    @ApiModelProperty(value = "是否有子节点", example = "true")
    private Boolean hasChildren;

    @ApiModelProperty(value = "子机构列表")
    private List<OrgTreeVO> children;
}
