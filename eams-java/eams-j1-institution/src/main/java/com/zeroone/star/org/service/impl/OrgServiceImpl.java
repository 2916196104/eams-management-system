package com.zeroone.star.org.service.impl;
import cn.hutool.core.collection.CollUtil;
import cn.hutool.core.util.StrUtil;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.org.entity.OrgDO;
import com.zeroone.star.org.mapper.OrgMapper;
import com.zeroone.star.org.service.IOrgService;
import com.zeroone.star.project.dto.j1.org.OrgSaveDTO;
import com.zeroone.star.project.query.j1.org.OrgQuery;
import com.zeroone.star.project.vo.j1.org.OrgDetailVO;
import com.zeroone.star.project.vo.j1.org.OrgListVO;
import com.zeroone.star.project.vo.j1.org.OrgTreeVO;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * 机构Service实现
 */
@Service
public class OrgServiceImpl extends ServiceImpl<OrgMapper, OrgDO> implements IOrgService {

    /**
     * 机构级别描述映射
     */
    private static final String[] ORG_LEVEL_DESC = {"", "集团", "分校", "部门"};

    /**
     * 状态描述映射
     */
    private static final String[] STATE_DESC = {"禁用", "启用"};

    @Override
    public List<OrgTreeVO> queryOrgTree(Long parentOrgId) {
        Long pid = (parentOrgId == null || parentOrgId == 0) ? 0L : parentOrgId;
        List<OrgDO> orgList = baseMapper.selectChildrenByPid(pid);

        if (CollUtil.isEmpty(orgList)) {
            return new ArrayList<>();
        }

        return orgList.stream().map(org -> {
            OrgTreeVO vo = new OrgTreeVO();
            vo.setOrgId(org.getId());
            vo.setOrgName(org.getName());
            vo.setParentOrgId(org.getPid());
            vo.setHasChildren(baseMapper.countChildrenByOrgId(org.getId()) > 0);
            return vo;
        }).collect(Collectors.toList());
    }

    @Override
    public List<OrgListVO> queryOrgList(OrgQuery query) {
        List<OrgDO> orgList = baseMapper.selectListByCondition(
                query.getOrgName(),
                query.getParentOrgId(),
                query.getOrgType(),
                query.getStatus()
        );

        if (CollUtil.isEmpty(orgList)) {
            return new ArrayList<>();
        }

        return orgList.stream().map(this::convertToListVO).collect(Collectors.toList());
    }

    @Override
    public OrgDetailVO queryOrgDetail(Long orgId) {
        if (orgId == null) {
            return null;
        }

        OrgDO org = baseMapper.selectDetailById(orgId);
        if (org == null) {
            return null;
        }

        return convertToDetailVO(org);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long saveOrg(OrgSaveDTO saveDTO, Long operatorId) {
        OrgDO orgDO = new OrgDO();
        LocalDateTime now = LocalDateTime.now();

        if (saveDTO.getOrgId() == null) {
            orgDO.setPid(saveDTO.getParentOrgId());
            orgDO.setName(saveDTO.getOrgName());
            orgDO.setShortname(saveDTO.getOrgShortName());
            orgDO.setLevel(saveDTO.getOrgType());
            orgDO.setState(saveDTO.getStatus() != null ? saveDTO.getStatus() : 1);
            orgDO.setContactName(saveDTO.getContact());
            orgDO.setPhone(saveDTO.getPhone());
            orgDO.setFax(saveDTO.getFax());
            orgDO.setEmail(saveDTO.getEmail());
            orgDO.setSortNum(saveDTO.getSortOrder() != null ? saveDTO.getSortOrder() : 0);
            orgDO.setInfo(saveDTO.getRemark());
            orgDO.setCreator(operatorId);
            orgDO.setAddTime(now);
            orgDO.setEditTime(now);
            orgDO.setDeleted(0);

            baseMapper.insert(orgDO);

            buildAndUpdatePath(orgDO);
        } else {
            orgDO = baseMapper.selectById(saveDTO.getOrgId());
            if (orgDO == null) {
                throw new RuntimeException("机构不存在");
            }

            boolean pidChanged = !orgDO.getPid().equals(saveDTO.getParentOrgId());

            orgDO.setPid(saveDTO.getParentOrgId());
            orgDO.setName(saveDTO.getOrgName());
            orgDO.setShortname(saveDTO.getOrgShortName());
            orgDO.setLevel(saveDTO.getOrgType());
            if (saveDTO.getStatus() != null) {
                orgDO.setState(saveDTO.getStatus());
            }
            orgDO.setContactName(saveDTO.getContact());
            orgDO.setPhone(saveDTO.getPhone());
            orgDO.setFax(saveDTO.getFax());
            orgDO.setEmail(saveDTO.getEmail());
            if (saveDTO.getSortOrder() != null) {
                orgDO.setSortNum(saveDTO.getSortOrder());
            }
            orgDO.setInfo(saveDTO.getRemark());
            orgDO.setEditor(operatorId);
            orgDO.setEditTime(now);

            baseMapper.updateById(orgDO);

            if (pidChanged) {
                buildAndUpdatePath(orgDO);
            }
        }

        return orgDO.getId();
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public boolean removeOrg(Long orgId) {
        if (orgId == null) {
            return false;
        }

        int childCount = baseMapper.countChildrenByOrgId(orgId);
        if (childCount > 0) {
            throw new RuntimeException("该机构存在子机构，不允许删除");
        }

        return removeById(orgId);
    }


    /**
     * 删除机构时多表查询校验是否有剩余员工
     */

    @Override
    @Transactional(rollbackFor = Exception.class)
    public boolean removeOrg(Long orgId) {
        if (orgId == null) {
            return false;
        }

        int childCount = baseMapper.countChildrenByOrgId(orgId);
        if (childCount > 0) {
            throw new RuntimeException("该机构存在子机构，不允许删除");
        }

        int staffCount = baseMapper.countStaffByOrgId(orgId);
        if (staffCount > 0) {
            throw new RuntimeException("该机构存在" + staffCount + "名员工，不允许删除");
        }

        return removeById(orgId);
    }





    /**
     * 构建并更新路径
     */
    private void buildAndUpdatePath(OrgDO org) {
        String idPath;
        String namePath;

        if (org.getPid() == null || org.getPid() == 0) {
            idPath = "/" + org.getId() + "/";
            namePath = "/" + org.getName() + "/";
        } else {
            OrgDO parent = baseMapper.selectDetailById(org.getPid());
            if (parent != null) {
                idPath = parent.getIdPath() + org.getId() + "/";
                namePath = parent.getNamePath() + org.getName() + "/";
            } else {
                idPath = "/" + org.getId() + "/";
                namePath = "/" + org.getName() + "/";
            }
        }

        org.setIdPath(idPath);
        org.setNamePath(namePath);
        baseMapper.updateById(org);
    }

    /**
     * 转换为列表VO
     */
    private OrgListVO convertToListVO(OrgDO org) {
        OrgListVO vo = new OrgListVO();
        vo.setOrgId(org.getId());
        vo.setOrgName(org.getName());
        vo.setOrgFullName(org.getNamePath() != null ?
                org.getNamePath().replace("/", " > ").replaceAll("^\\s*>\\s*|\\s*>\\s*$", "") :
                org.getName());
        vo.setOrgType(org.getLevel());
        vo.setOrgTypeDesc(getOrgLevelDesc(org.getLevel()));
        vo.setContact(org.getContactName());
        vo.setPhone(org.getPhone());
        vo.setParentOrgId(org.getPid());
        return vo;
    }

    /**
     * 转换为详情VO
     */
    private OrgDetailVO convertToDetailVO(OrgDO org) {
        OrgDetailVO vo = new OrgDetailVO();
        vo.setOrgId(org.getId());
        vo.setOrgName(org.getName());
        vo.setOrgType(org.getLevel());
        vo.setOrgTypeDesc(getOrgLevelDesc(org.getLevel()));
        vo.setOrgShortName(org.getShortname());
        vo.setBusinessLicense(org.getLicense());
        vo.setContact(org.getContactName());
        vo.setRegion(buildRegionStr(org.getProvince(), org.getCity(), org.getDistrict(), org.getAddress()));
        vo.setPhone(org.getPhone());
        vo.setFax(org.getFax());
        vo.setEmail(org.getEmail());
        vo.setSortOrder(org.getSortNum());
        vo.setStatus(org.getState());
        vo.setStatusDesc(getStateDesc(org.getState()));
        vo.setRemark(org.getInfo());
        vo.setParentOrgId(org.getPid());

        if (org.getPid() != null && org.getPid() > 0) {
            String parentName = baseMapper.selectParentNameById(org.getPid());
            vo.setParentOrgName(parentName);
        }

        return vo;
    }

    /**
     * 获取机构级别描述
     */
    private String getOrgLevelDesc(Integer level) {
        if (level == null || level < 1 || level >= ORG_LEVEL_DESC.length) {
            return "";
        }
        return ORG_LEVEL_DESC[level];
    }

    /**
     * 获取状态描述
     */
    private String getStateDesc(Integer state) {
        if (state == null || state < 0 || state >= STATE_DESC.length) {
            return "";
        }
        return STATE_DESC[state];
    }

    /**
     * 构建地区字符串
     */
    private String buildRegionStr(Integer province, Integer city, Integer district, String address) {
        StringBuilder sb = new StringBuilder();
        if (StrUtil.isNotBlank(address)) {
            sb.append(address);
        }
        return sb.toString();
    }
}
