package com.zeroone.star.org.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.org.entity.OrgDO;
import com.zeroone.star.project.dto.j1.org.OrgSaveDTO;
import com.zeroone.star.project.query.j1.org.OrgQuery;
import com.zeroone.star.project.vo.j1.org.OrgDetailVO;
import com.zeroone.star.project.vo.j1.org.OrgListVO;
import com.zeroone.star.project.vo.j1.org.OrgTreeVO;

import java.util.List;

/**
 * 机构Service接口
 */
public interface IOrgService extends IService<OrgDO> {

    /**
     * 查询机构树
     * @param parentOrgId 父机构ID，为null或0时查询一级节点
     * @return 机构树列表
     */
    List<OrgTreeVO> queryOrgTree(Long parentOrgId);

    /**
     * 查询机构列表
     * @param query 查询条件
     * @return 机构列表
     */
    List<OrgListVO> queryOrgList(OrgQuery query);

    /**
     * 查询机构详情
     * @param orgId 机构ID
     * @return 机构详情
     */
    OrgDetailVO queryOrgDetail(Long orgId);

    /**
     * 保存机构（新增或修改）
     * @param saveDTO 保存数据
     * @param operatorId 操作人ID
     * @return 机构ID
     */
    Long saveOrg(OrgSaveDTO saveDTO, Long operatorId);

    /**
     * 删除机构
     * @param orgId 机构ID
     * @return 是否删除成功
     */
    boolean removeOrg(Long orgId);
}
