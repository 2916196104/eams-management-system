package com.zeroone.star.org.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.org.entity.OrgDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

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
    @Select("SELECT id, pid, name, level FROM org WHERE pid = #{pid} AND deleted = 0 ORDER BY sort_num ASC")
    List<OrgDO> selectChildrenByPid(@Param("pid") Long pid);

    /**
     * 查询机构是否有子机构
     * @param orgId 机构ID
     * @return 子机构数量
     */
    @Select("SELECT COUNT(1) FROM org WHERE pid = #{orgId} AND deleted = 0")
    int countChildrenByOrgId(@Param("orgId") Long orgId);

    /**
     * 根据ID查询机构详情（不使用select *）
     * @param orgId 机构ID
     * @return 机构详情
     */
    @Select("SELECT id, pid, name, shortname, level, state, contact_name, phone, fax, email, " +
            "province, city, district, address, sort_num, license, info, id_path, name_path " +
            "FROM org WHERE id = #{orgId} AND deleted = 0")
    OrgDO selectDetailById(@Param("orgId") Long orgId);

    /**
     * 根据条件查询机构列表
     * @param orgName 机构名称（模糊查询）
     * @param parentOrgId 父机构ID
     * @param orgType 机构级别
     * @param status 状态
     * @return 机构列表
     */
    @Select("<script>" +
            "SELECT id, pid, name, shortname, level, state, contact_name, phone, name_path " +
            "FROM org WHERE deleted = 0 " +
            "<if test='orgName != null and orgName != \"\"'> AND name LIKE CONCAT('%', #{orgName}, '%')</if>" +
            "<if test='parentOrgId != null'> AND pid = #{parentOrgId}</if>" +
            "<if test='orgType != null'> AND level = #{orgType}</if>" +
            "<if test='status != null'> AND state = #{status}</if>" +
            " ORDER BY sort_num ASC, id ASC" +
            "</script>")
    List<OrgDO> selectListByCondition(@Param("orgName") String orgName,
                                       @Param("parentOrgId") Long parentOrgId,
                                       @Param("orgType") Integer orgType,
                                       @Param("status") Integer status);

    /**
     * 查询父机构名称
     * @param pid 父机构ID
     * @return 父机构名称
     */
    @Select("SELECT name FROM org WHERE id = #{pid} AND deleted = 0")
    String selectParentNameById(@Param("pid") Long pid);

    /**
     * 统计机构下的员工数量
     * @param orgId 机构ID
     * @return 员工数量
     */
    @Select("SELECT COUNT(1) FROM staff WHERE org_id = #{orgId} AND deleted = 0")
    int countStaffByOrgId(@Param("orgId") Long orgId);
}