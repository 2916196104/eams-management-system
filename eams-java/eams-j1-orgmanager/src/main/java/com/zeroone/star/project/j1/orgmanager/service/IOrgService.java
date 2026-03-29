package com.zeroone.star.project.j1.orgmanager.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.DO.OrgDO;
import com.zeroone.star.project.dto.j1.org.OrgSaveDTO;
import com.zeroone.star.project.query.j1.org.OrgQuery;
import com.zeroone.star.project.vo.j1.org.OrgDetailVO;
import com.zeroone.star.project.vo.j1.org.OrgListVO;
import com.zeroone.star.project.vo.j1.org.OrgTreeVO;

import java.util.List;

/**
 * <p>
 * 机构管理 服务类
 * </p>
 *
 * @author 康康舞曲
 * @since 1.0.0
 */
public interface IOrgService extends IService<OrgDO> {

    /**
     * 查询机构树
     * @param parentOrgId 父机构ID，为null或0时查询一级节点
     * @param operatorOrgId 操作人所属机构ID（用于数据权限隔离）
     * @return 机构树列表
     */
    List<OrgTreeVO> queryOrgTree(Long parentOrgId, Long operatorOrgId);

    /**
     * 查询机构列表
     * @param query 查询条件
     * @param operatorOrgId 操作人所属机构ID（用于数据权限隔离）
     * @return 机构列表
     */
    List<OrgListVO> queryOrgList(OrgQuery query, Long operatorOrgId);

    /**
     * 查询机构详情
     * @param orgId 机构ID
     * @param operatorOrgId 操作人所属机构ID（用于数据权限隔离）
     * @return 机构详情
     */
    OrgDetailVO queryOrgDetail(Long orgId, Long operatorOrgId);

    /**
     * 保存机构（新增或修改）
     * @param saveDTO 保存数据
     * @param operatorId 操作人ID
     * @param operatorOrgId 操作人所属机构ID（用于数据权限隔离）
     * @return 机构ID
     */
    Long saveOrg(OrgSaveDTO saveDTO, Long operatorId, Long operatorOrgId);

    /**
     * 删除机构
     * @param orgId 机构ID
     * @param operatorOrgId 操作人所属机构ID（用于数据权限隔离）
     * @return 是否删除成功
     */
    boolean removeOrg(Long orgId, Long operatorOrgId);
}
