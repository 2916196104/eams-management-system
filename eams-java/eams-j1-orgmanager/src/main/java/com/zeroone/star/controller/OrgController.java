package com.zeroone.star.controller;


import com.zeroone.star.project.dto.j1.org.OrgSaveDTO;
import com.zeroone.star.project.j1.org.OrgApi;
import com.zeroone.star.project.query.j1.org.OrgQuery;
import com.zeroone.star.project.vo.j1.org.OrgDetailVO;
import com.zeroone.star.project.vo.j1.org.OrgListVO;
import com.zeroone.star.project.vo.j1.org.OrgTreeVO;


import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.RestController;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * 机构管理接口实现（仅返回示例数据，无Service/DAO层，目前就先保证接口文档可用）
 */
@RestController
@Slf4j
public class OrgController implements OrgApi {

    @Override
    public List<OrgTreeVO> queryOrgTree() {
        // 模拟机构树形数据
        List<OrgTreeVO> treeList = new ArrayList<>();

        // 总校节点
        OrgTreeVO root = new OrgTreeVO();
        root.setOrgId(1000L);
        root.setOrgName("零壹教育总校");
        root.setParentOrgId(0L);

        // 分校子节点
        OrgTreeVO branch = new OrgTreeVO();
        branch.setOrgId(1001L);
        branch.setOrgName("零壹教育海淀分校");
        branch.setParentOrgId(1000L);

        // 校区子节点
        OrgTreeVO campus = new OrgTreeVO();
        campus.setOrgId(1002L);
        campus.setOrgName("海淀分校中关村校区");
        campus.setParentOrgId(1001L);
        List<OrgTreeVO> campusList = new ArrayList<>();
        campusList.add(campus);
        branch.setChildren(campusList);

        List<OrgTreeVO> branchList = new ArrayList<>();
        branchList.add(branch);
        root.setChildren(branchList);

        treeList.add(root);
        return treeList;
    }

    @Override
    public List<OrgListVO> queryOrgList(OrgQuery query) {
        // 模拟机构列表数据
        List<OrgListVO> listVO = new ArrayList<>();
        OrgListVO vo = new OrgListVO();
        vo.setOrgId(1001L);
        vo.setOrgName("零壹教育海淀分校");
        vo.setOrgCode("LD-HD-001");
        vo.setParentOrgId(1000L);
        vo.setParentOrgName("零壹教育总校");
        vo.setOrgType(2);
        vo.setOrgTypeDesc("分校");
        vo.setContact("王经理");
        vo.setPhone("13800138000");
        vo.setStatus(1);
        vo.setStatusDesc("启用");
        vo.setCreateTime(new Date());
        vo.setUpdateTime(new Date());
        listVO.add(vo);
        return listVO;
    }

    @Override
    public OrgDetailVO queryOrgDetail(Long orgId) {
        // 模拟机构详情数据
        OrgDetailVO detailVO = new OrgDetailVO();
        detailVO.setOrgId(orgId);
        detailVO.setOrgName("零壹教育海淀分校");
        detailVO.setOrgCode("LD-HD-001");
        detailVO.setParentOrgId(1000L);
        detailVO.setParentOrgName("零壹教育总校");
        detailVO.setOrgType(2);
        detailVO.setOrgTypeDesc("分校");
        detailVO.setContact("王经理");
        detailVO.setPhone("13800138000");
        detailVO.setAddress("北京市海淀区XX路XX号");
        detailVO.setRemark("2026年新成立分校");
        detailVO.setStatus(1);
        detailVO.setStatusDesc("启用");
        detailVO.setCreateBy("admin");
        detailVO.setCreateTime(new Date());
        detailVO.setUpdateBy("admin");
        detailVO.setUpdateTime(new Date());
        return detailVO;
    }

    @Override
    public String saveOrg(OrgSaveDTO saveDTO) {
        // 模拟保存结果（新增/修改区分）
        if (saveDTO.getOrgId() == null) {
            return "新增机构成功，机构ID：1003";
        } else {
            return "修改机构成功，机构ID：" + saveDTO.getOrgId();
        }
    }

    @Override
    public Boolean removeOrg(Long orgId) {
        // 模拟删除成功（实际需校验子机构/关联数据，此处仅返回结果）
        return true;
    }
}