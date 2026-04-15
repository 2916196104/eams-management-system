package com.zeroone.star.sys.service.roleperm;

import com.zeroone.star.sys.entity.SysPermission;
import com.baomidou.mybatisplus.extension.service.IService;

import java.util.List;

/**
 * <p>
 * 权限 服务类
 * </p>
 *
 * @author Yaco
 * @since 2026-03-21
 */
public interface SysPermissionService extends IService<SysPermission> {
   //获取可分配的权限
    public List<SysPermission> queryPermission();
    //获取已分配的权限
    public List<SysPermission> querySelectedPermission(String roleId);
    //保存已分配的权限
    public boolean savePermission(String roleId, List<SysPermission> permissions);

}
