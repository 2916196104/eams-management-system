package com.zeroone.star.project.j1.org;


import com.zeroone.star.project.dto.j1.org.OrgSaveDTO;
import com.zeroone.star.project.query.j1.org.OrgQuery;
import com.zeroone.star.project.vo.j1.org.OrgDetailVO;
import com.zeroone.star.project.vo.j1.org.OrgListVO;
import com.zeroone.star.project.vo.j1.org.OrgTreeVO;


import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.Tag;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.List;

/**
 * 机构管理接口
 */
@RequestMapping("/org")
public interface OrgApi {

    @ApiOperation(value = "获取机构名称树查询所有机构的层级树形结构，仅返回ID和名称")
    @GetMapping("/query-org-tree")
    List<OrgTreeVO> queryOrgTree();

    @ApiOperation(value = "获取机构列表（条件）根据机构名称/父ID/状态/类型等条件查询机构列表")
    @GetMapping("/query-list")
    List<OrgListVO> queryOrgList( OrgQuery query);

    @ApiOperation(value = "获取机构详情" )
    @GetMapping("/query-detail")
    OrgDetailVO queryOrgDetail( @RequestParam Long orgId);

    @ApiOperation(value = "保存机构")
    @PostMapping("/save-org")
    String saveOrg(@Valid @RequestBody OrgSaveDTO saveDTO);

    @ApiOperation(value = "删除机构")
    @DeleteMapping("/remove-org")
    Boolean removeOrg(@RequestParam Long orgId);
}