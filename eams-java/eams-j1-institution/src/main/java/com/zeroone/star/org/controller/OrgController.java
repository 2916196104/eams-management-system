package com.zeroone.star.org.controller;

import com.zeroone.star.project.dto.j1.org.OrgSaveDTO;
import com.zeroone.star.project.j1.org.OrgApi;
import com.zeroone.star.project.query.j1.org.OrgQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.OrgDetailVO;
import com.zeroone.star.project.vo.j1.org.OrgListVO;
import com.zeroone.star.project.vo.j1.org.OrgTreeVO;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.RestController;

import java.util.ArrayList;
import java.util.List;

/**
 * 机构管理接口实现（仅返回示例数据，无Service/DAO层，目前就先保证接口文档可用）
 */
@RestController
@Slf4j
public class OrgController implements OrgApi {

    @Override
    public JsonVO<List<OrgTreeVO>> queryOrgTree(Long parentOrgId) {
        // 如果parentOrgId为null或0，查询一级节点
        Long pid = (parentOrgId == null || parentOrgId == 0) ? 0L : parentOrgId;

        // 模拟机构树形数据
        List<OrgTreeVO> treeList = new ArrayList<>();

        if (pid == 0L) {
            // 查询一级节点（集团）
            OrgTreeVO root = new OrgTreeVO();
            root.setOrgId(1000L);
            root.setOrgName("零壹教育集团");
            root.setParentOrgId(0L);
            root.setHasChildren(true);
            treeList.add(root);
        } else if (pid == 1000L) {
            // 查询集团下的分校
            OrgTreeVO branch1 = new OrgTreeVO();
            branch1.setOrgId(1001L);
            branch1.setOrgName("零壹教育海淀分校");
            branch1.setParentOrgId(1000L);
            branch1.setHasChildren(true);

            OrgTreeVO branch2 = new OrgTreeVO();
            branch2.setOrgId(1002L);
            branch2.setOrgName("零壹教育朝阳分校");
            branch2.setParentOrgId(1000L);
            branch2.setHasChildren(false);

            treeList.add(branch1);
            treeList.add(branch2);
        } else if (pid == 1001L) {
            // 查询分校下的部门
            OrgTreeVO dept1 = new OrgTreeVO();
            dept1.setOrgId(2001L);
            dept1.setOrgName("教务部");
            dept1.setParentOrgId(1001L);
            dept1.setHasChildren(false);

            OrgTreeVO dept2 = new OrgTreeVO();
            dept2.setOrgId(2002L);
            dept2.setOrgName("市场部");
            dept2.setParentOrgId(1001L);
            dept2.setHasChildren(false);

            treeList.add(dept1);
            treeList.add(dept2);
        }

        return JsonVO.success(treeList);
    }

    @Override
    public JsonVO<List<OrgListVO>> queryOrgList(OrgQuery query) {
        // 模拟机构列表数据
        List<OrgListVO> listVO = new ArrayList<>();

        OrgListVO vo1 = new OrgListVO();
        vo1.setOrgId(1001L);
        vo1.setOrgName("零壹教育海淀分校");
        vo1.setOrgFullName("北京零壹教育科技有限公司海淀分公司");
        vo1.setOrgType(2);
        vo1.setOrgTypeDesc("分校");
        vo1.setContact("王经理");
        vo1.setPhone("13800138000");
        vo1.setParentOrgId(1000L);
        listVO.add(vo1);

        OrgListVO vo2 = new OrgListVO();
        vo2.setOrgId(1002L);
        vo2.setOrgName("零壹教育朝阳分校");
        vo2.setOrgFullName("北京零壹教育科技有限公司朝阳分公司");
        vo2.setOrgType(2);
        vo2.setOrgTypeDesc("分校");
        vo2.setContact("李经理");
        vo2.setPhone("13900139000");
        vo2.setParentOrgId(1000L);
        listVO.add(vo2);

        return JsonVO.success(listVO);
    }

    @Override
    public JsonVO<OrgDetailVO> queryOrgDetail(Long orgId) {
        // 模拟机构详情数据
        OrgDetailVO detailVO = new OrgDetailVO();
        detailVO.setOrgId(orgId);
        detailVO.setOrgName("零壹教育海淀分校");
        detailVO.setOrgType(2);
        detailVO.setOrgTypeDesc("分校");
        detailVO.setOrgShortName("海淀分校");
        detailVO.setBusinessLicense("91110108MA01XXXXX");
        detailVO.setContact("王经理");
        detailVO.setRegion("北京市海淀区");
        detailVO.setPhone("13800138000");
        detailVO.setFax("010-12345678");
        detailVO.setEmail("haidian@zeroone.com");
        detailVO.setSortOrder(1);
        detailVO.setStatus(1);
        detailVO.setStatusDesc("启用");
        detailVO.setRemark("2026年新成立分校");
        detailVO.setParentOrgId(1000L);
        detailVO.setParentOrgName("零壹教育集团");

        return JsonVO.success(detailVO);
    }

    @Override
    public JsonVO<String> saveOrg(OrgSaveDTO saveDTO) {
        // 模拟保存结果（新增/修改区分）
        if (saveDTO.getOrgId() == null) {
            log.info("新增机构：{}", saveDTO.getOrgName());
            return JsonVO.success("新增机构成功，机构ID：1003");
        } else {
            log.info("修改机构：ID={}, 名称={}", saveDTO.getOrgId(), saveDTO.getOrgName());
            return JsonVO.success("修改机构成功，机构ID：" + saveDTO.getOrgId());
        }
    }

    @Override
    public JsonVO<Boolean> removeOrg(Long orgId) {
        // 模拟删除（实际需校验子机构）
        // 如果有子机构，应该返回失败
        log.info("删除机构：ID={}", orgId);

        // 模拟：假设机构1001有子机构，不允许删除
        if (orgId == 1001L) {
            return JsonVO.fail("该机构存在子机构，不允许删除");
        }

        return JsonVO.success(true);
    }
}
