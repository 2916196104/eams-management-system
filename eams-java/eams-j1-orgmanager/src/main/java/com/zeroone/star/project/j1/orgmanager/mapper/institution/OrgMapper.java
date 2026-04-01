package com.zeroone.star.project.j1.orgmanager.mapper.institution;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.DO.OrgDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * 机构 Mapper 接口
 * </p>
 *
 * @author 康康舞曲
 * @since 1.0.0
 */
@Mapper
public interface OrgMapper extends BaseMapper<OrgDO> {

    /**
     * 根据父ID查询子机构列表（仅查询树形需要的字段）
     * @param pid 父机构ID
     * @param idPathPrefix 机构ID路径前缀（用于数据权限隔离）
     * @return 机构列表
     */
    List<OrgDO> selectChildrenByPid(@Param("pid") Long pid, @Param("idPathPrefix") String idPathPrefix);

    /**
     * 查询机构是否有子机构
     * @param orgId 机构ID
     * @param idPathPrefix 机构ID路径前缀（用于数据权限隔离）
     * @return 子机构数量
     */
    int countChildrenByOrgId(@Param("orgId") Long orgId, @Param("idPathPrefix") String idPathPrefix);

    /**
     * 根据ID查询机构详情
     * @param orgId 机构ID
     * @param idPathPrefix 机构ID路径前缀（用于数据权限隔离）
     * @return 机构详情
     */
    OrgDO selectDetailById(@Param("orgId") Long orgId, @Param("idPathPrefix") String idPathPrefix);

    /**
     * 根据条件查询机构列表
     * @param orgName 机构名称（模糊查询）
     * @param parentOrgId 父机构ID
     * @param orgType 机构级别
     * @param status 状态
     * @param idPathPrefix 机构ID路径前缀（用于数据权限隔离）
     * @return 机构列表
     */
    List<OrgDO> selectListByCondition(@Param("orgName") String orgName,
                                       @Param("parentOrgId") Long parentOrgId,
                                       @Param("orgType") Integer orgType,
                                       @Param("status") Integer status,
                                       @Param("idPathPrefix") String idPathPrefix);

    /**
     * 查询父机构名称
     * @param pid 父机构ID
     * @param idPathPrefix 机构ID路径前缀（用于数据权限隔离）
     * @return 父机构名称
     */
    String selectParentNameById(@Param("pid") Long pid, @Param("idPathPrefix") String idPathPrefix);

    /**
     * 统计机构下的员工数量（通过 staff_orginfo 关联表查询）
     * @param orgId 机构ID
     * @return 员工数量
     */
    int countStaffByOrgId(@Param("orgId") Long orgId);

    /**
     * 根据机构ID查询idPath
     * @param orgId 机构ID
     * @return idPath
     */
    String selectIdPathById(@Param("orgId") Long orgId);
}
