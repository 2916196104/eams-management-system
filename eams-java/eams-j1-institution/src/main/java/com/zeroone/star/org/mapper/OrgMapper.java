package com.zeroone.star.org.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.org.entity.OrgDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * 机构Mapper接口
 */
@Mapper
public interface OrgMapper extends BaseMapper<OrgDO> {

    /**
     * 根据父ID查询子机构列表（仅查询树形需要的字段）
     * @param pid 父机构ID
     * @return 机构列表
     */
    List<OrgDO> selectChildrenByPid(@Param("pid") Long pid);

    /**
     * 查询机构是否有子机构
     * @param orgId 机构ID
     * @return 子机构数量
     */
    int countChildrenByOrgId(@Param("orgId") Long orgId);

    /**
     * 根据ID查询机构详情
     * @param orgId 机构ID
     * @return 机构详情
     */
    OrgDO selectDetailById(@Param("orgId") Long orgId);

    /**
     * 根据条件查询机构列表
     * @param orgName 机构名称（模糊查询）
     * @param parentOrgId 父机构ID
     * @param orgType 机构级别
     * @param status 状态
     * @return 机构列表
     */
    List<OrgDO> selectListByCondition(@Param("orgName") String orgName,
                                       @Param("parentOrgId") Long parentOrgId,
                                       @Param("orgType") Integer orgType,
                                       @Param("status") Integer status);

    /**
     * 查询父机构名称
     * @param pid 父机构ID
     * @return 父机构名称
     */
    String selectParentNameById(@Param("pid") Long pid);

    /**
     * 统计机构下的员工数量（通过 staff_orginfo 关联表查询）
     * @param orgId 机构ID
     * @return 员工数量
     */
    int countStaffByOrgId(@Param("orgId") Long orgId);
}
