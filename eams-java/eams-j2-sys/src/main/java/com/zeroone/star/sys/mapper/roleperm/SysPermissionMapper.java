package com.zeroone.star.sys.mapper.roleperm;

import com.zeroone.star.sys.entity.SysPermission;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.*;

import java.util.List;

/**
 * <p>
 * 权限 Mapper 接口
 * </p>
 *
 * @author Yaco
 * @since 2026-03-21
 */
@Mapper
public interface SysPermissionMapper extends BaseMapper<SysPermission> {
    //获取可分配的权限
    @Select("select * from sys_permission")
    public List<SysPermission> queryPermission();
    //获取已分配的权限
    @Select("select * from sys_permission where id in (select permission_id from sys_role_permission where role_id=#{roleId})")
    public List<SysPermission> querySelectedPermission(@Param("roleId") String roleId);

    public Long deletePermissionByRoleId(@Param("roleId") String roleId);
    //保存已分配的权限
    public Long savePermission(@Param("roleId") String roleId, @Param("permissions")List<SysPermission> permissions);
}
