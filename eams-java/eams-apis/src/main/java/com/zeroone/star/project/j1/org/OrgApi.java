package com.zeroone.star.project.j1.org;


import com.zeroone.star.project.dto.j1.org.OrgSaveDTO;
import com.zeroone.star.project.query.j1.org.OrgQuery;
import com.zeroone.star.project.vo.j1.org.OrgDetailVO;
import com.zeroone.star.project.vo.j1.org.OrgListVO;
import com.zeroone.star.project.vo.j1.org.OrgTreeVO;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.Parameter;
import io.swagger.v3.oas.annotations.tags.Tag;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.List;

/**
 * 机构管理接口
 */
@Tag(name = "机构管理", description = "组织页面-机构信息查询、保存、删除接口")
@RequestMapping("/org")
public interface OrgApi {

    @Operation(summary = "获取机构名称树", description = "查询所有机构的层级树形结构，仅返回ID和名称")
    @GetMapping("/query-org-tree")
    List<OrgTreeVO> queryOrgTree();

    @Operation(summary = "获取机构列表（条件）", description = "根据机构名称/父ID/状态/类型等条件查询机构列表")
    @GetMapping("/query-list")
    List<OrgListVO> queryOrgList(@Parameter(description = "机构查询参数") OrgQuery query);

    @Operation(summary = "获取机构详情", description = "根据机构ID查询机构完整信息")
    @GetMapping("/query-detail")
    OrgDetailVO queryOrgDetail(@Parameter(description = "机构ID", required = true, example = "1001") @RequestParam Long orgId);

    @Operation(summary = "保存机构", description = "新增/修改机构信息（有ID则修改，无ID则新增）")
    @PostMapping("/save-org")
    String saveOrg(@Valid @RequestBody OrgSaveDTO saveDTO);

    @Operation(summary = "删除机构", description = "根据机构ID删除机构（需校验是否有子机构/关联数据）")
    @DeleteMapping("/remove-org")
    Boolean removeOrg(@Parameter(description = "机构ID", required = true, example = "1001") @RequestParam Long orgId);
}