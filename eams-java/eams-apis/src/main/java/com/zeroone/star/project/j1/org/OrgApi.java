package com.zeroone.star.project.j1.org;

import com.zeroone.star.project.dto.j1.org.OrgSaveDTO;
import com.zeroone.star.project.query.j1.org.OrgQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.OrgDetailVO;
import com.zeroone.star.project.vo.j1.org.OrgListVO;
import com.zeroone.star.project.vo.j1.org.OrgTreeVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.List;

/**
 * 机构管理接口
 */
@Api(tags = "机构管理")
@RequestMapping("/org/institution")
public interface OrgApi {

    @ApiOperation(value = "获取机构树", notes = "根据parentOrgId查询机构树，parentOrgId为0或null时查询一级节点")
    @GetMapping("/query-org-tree")
    JsonVO<List<OrgTreeVO>> queryOrgTree(@RequestParam(required = false) Long parentOrgId);

    @ApiOperation(value = "获取机构列表", notes = "根据条件查询机构列表，返回关键数据，完整数据通过详情接口获取")
    @GetMapping("/query-list")
    JsonVO<List<OrgListVO>> queryOrgList(@ModelAttribute OrgQuery query);

    @ApiOperation(value = "获取机构详情", notes = "根据机构ID获取完整信息")
    @GetMapping("/query-detail")
    JsonVO<OrgDetailVO> queryOrgDetail(@RequestParam Long orgId);

    @ApiOperation(value = "保存机构", notes = "新增或修改机构，orgId为空时新增，不为空时修改")
    @PostMapping("/save-org")
    JsonVO<String> saveOrg(@Valid @RequestBody OrgSaveDTO saveDTO);

    @ApiOperation(value = "删除机构", notes = "删除机构，若有子机构则不允许删除")
    @DeleteMapping("/remove-org")
    JsonVO<Boolean> removeOrg(@RequestParam Long orgId);
}
