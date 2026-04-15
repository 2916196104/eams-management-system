package com.zeroone.star.project.j1.orgmanager.service.impl;

import cn.hutool.core.collection.CollUtil;
import cn.hutool.core.util.StrUtil;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.DO.OrgDO;
import com.zeroone.star.project.dto.j1.org.OrgSaveDTO;
import com.zeroone.star.project.j1.orgmanager.mapper.institution.OrgMapper;
import com.zeroone.star.project.j1.orgmanager.service.IOrgService;
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
 * <p>
 * 机构管理 服务实现类
 * </p>
 *
 * @author 阿伟学长
 * @since 1.0.0
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

    /**
     * 判断是否为系统管理员（根机构级别，可以操作所有机构）
     * @param operatorOrgId 操作人所属机构ID
     * @return 是否为管理员
     */
    private boolean isAdmin(Long operatorOrgId) {
        // 如果orgId为null、0、1或1000，认为是管理员，可以操作所有机构
        // 1=学校总部, 1000=零壹教育集团，都是根机构
        return operatorOrgId == null || operatorOrgId == 0L || operatorOrgId == 1L || operatorOrgId == 1000L;
    }

    /**
     * 构建数据权限过滤的idPath前缀
     * @param operatorOrgId 操作人所属机构ID
     * @return idPath前缀，如 "/1/"；如果是管理员返回null表示不限
     */
    private String buildIdPathPrefix(Long operatorOrgId) {
        // 管理员不限制数据权限
        if (isAdmin(operatorOrgId)) {
            return null;
        }
        // 查询操作人所属机构的idPath
        String idPath = baseMapper.selectIdPathById(operatorOrgId);
        if (StrUtil.isBlank(idPath)) {
            // 如果查不到，使用默认格式
            return "/" + operatorOrgId + "/";
        }
        return idPath;
    }

    /**
     * 校验机构是否在操作人权限范围内
     * @param orgId 要操作的机构ID
     * @param operatorOrgId 操作人所属机构ID
     * @return 是否有权限
     */
    private boolean checkOrgPermission(Long orgId, Long operatorOrgId) {
        if (orgId == null) {
            return false;
        }
        // 管理员有所有权限
        if (isAdmin(operatorOrgId)) {
            return true;
        }
        if (operatorOrgId == null) {
            return false;
        }
        // 查询机构详情（带权限过滤）
        OrgDO org = baseMapper.selectDetailById(orgId, buildIdPathPrefix(operatorOrgId));
        return org != null;
    }

    @Override
    public List<OrgTreeVO> queryOrgTree(Long parentOrgId, Long operatorOrgId) {
        String idPathPrefix = buildIdPathPrefix(operatorOrgId);
        Long pid = (parentOrgId == null || parentOrgId == 0) ? 0L : parentOrgId;

        // 校验是否有权限查看该父机构下的数据（管理员跳过）
        if (!isAdmin(operatorOrgId) && pid != 0 && !checkOrgPermission(pid, operatorOrgId)) {
            return new ArrayList<>();
        }

        List<OrgDO> orgList = baseMapper.selectChildrenByPid(pid, idPathPrefix);

        if (CollUtil.isEmpty(orgList)) {
            return new ArrayList<>();
        }

        return orgList.stream().map(org -> {
            OrgTreeVO vo = new OrgTreeVO();
            vo.setOrgId(org.getId());
            vo.setOrgName(org.getName());
            vo.setParentOrgId(org.getPid());
            vo.setHasChildren(baseMapper.countChildrenByOrgId(org.getId(), idPathPrefix) > 0);
            return vo;
        }).collect(Collectors.toList());
    }

    @Override
    public List<OrgListVO> queryOrgList(OrgQuery query, Long operatorOrgId) {
        String idPathPrefix = buildIdPathPrefix(operatorOrgId);

        // 如果指定了父机构ID，校验权限（管理员跳过）
        if (!isAdmin(operatorOrgId) && query != null && query.getParentOrgId() != null && query.getParentOrgId() != 0) {
            if (!checkOrgPermission(query.getParentOrgId(), operatorOrgId)) {
                return new ArrayList<>();
            }
        }

        List<OrgDO> orgList = baseMapper.selectListByCondition(
                query != null ? query.getOrgName() : null,
                query != null ? query.getParentOrgId() : null,
                query != null ? query.getOrgType() : null,
                query != null ? query.getStatus() : null,
                idPathPrefix
        );

        if (CollUtil.isEmpty(orgList)) {
            return new ArrayList<>();
        }

        return orgList.stream().map(this::convertToListVO).collect(Collectors.toList());
    }

    @Override
    public OrgDetailVO queryOrgDetail(Long orgId, Long operatorOrgId) {
        if (orgId == null) {
            return null;
        }

        String idPathPrefix = buildIdPathPrefix(operatorOrgId);
        OrgDO org = baseMapper.selectDetailById(orgId, idPathPrefix);
        if (org == null) {
            return null;
        }

        return convertToDetailVO(org, idPathPrefix);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long saveOrg(OrgSaveDTO saveDTO, Long operatorId, Long operatorOrgId) {
        // 数据权限校验：只能在自己机构范围内新增/修改
        String idPathPrefix = buildIdPathPrefix(operatorOrgId);

        OrgDO orgDO = new OrgDO();
        LocalDateTime now = LocalDateTime.now();

        if (saveDTO.getOrgId() == null) {
            // 新增：校验父机构权限（管理员跳过）
            if (!isAdmin(operatorOrgId) && !checkOrgPermission(saveDTO.getParentOrgId(), operatorOrgId)) {
                throw new RuntimeException("无权在该父机构下创建子机构");
            }

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
            // 修改：校验当前机构权限（管理员跳过）
            if (!isAdmin(operatorOrgId) && !checkOrgPermission(saveDTO.getOrgId(), operatorOrgId)) {
                throw new RuntimeException("无权修改该机构");
            }

            orgDO = baseMapper.selectDetailById(saveDTO.getOrgId(), idPathPrefix);
            if (orgDO == null) {
                throw new RuntimeException("机构不存在");
            }

            // 如果修改了父机构，校验新父机构权限（管理员跳过）
            boolean pidChanged = !orgDO.getPid().equals(saveDTO.getParentOrgId());
            if (!isAdmin(operatorOrgId) && pidChanged && !checkOrgPermission(saveDTO.getParentOrgId(), operatorOrgId)) {
                throw new RuntimeException("无权将该机构移动到目标父机构下");
            }

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
    public boolean removeOrg(Long orgId, Long operatorOrgId) {
        if (orgId == null) {
            return false;
        }

        // 数据权限校验（管理员跳过）
        if (!isAdmin(operatorOrgId) && !checkOrgPermission(orgId, operatorOrgId)) {
            throw new RuntimeException("无权删除该机构");
        }

        String idPathPrefix = buildIdPathPrefix(operatorOrgId);

        int childCount = baseMapper.countChildrenByOrgId(orgId, idPathPrefix);
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
            OrgDO parent = baseMapper.selectById(org.getPid());
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
    private OrgDetailVO convertToDetailVO(OrgDO org, String idPathPrefix) {
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
            String parentName = baseMapper.selectParentNameById(org.getPid(), idPathPrefix);
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
