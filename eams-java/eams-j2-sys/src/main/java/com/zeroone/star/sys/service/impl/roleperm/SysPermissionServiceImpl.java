package com.zeroone.star.sys.service.impl.roleperm;

import com.zeroone.star.sys.entity.SysPermission;
import com.zeroone.star.sys.mapper.roleperm.SysPermissionMapper;
import com.zeroone.star.sys.service.roleperm.SysPermissionService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

/**
 * <p>
 * 权限 服务实现类
 * </p>
 *
 * @author Yaco
 * @since 2026-03-21
 */
@Service
@Transactional(rollbackFor = Exception.class)
public class SysPermissionServiceImpl extends ServiceImpl<SysPermissionMapper, SysPermission> implements SysPermissionService {
    //获取可分配的权限
    @Override
    public List<SysPermission> queryPermission() {
        List<SysPermission> permissions =baseMapper.queryPermission();
        return permissions;
    }
    //获取已分配的权限
    @Override
    public List<SysPermission> querySelectedPermission(String roleId) {
        List<SysPermission> Exitspermissions =baseMapper.querySelectedPermission(roleId);
        return Exitspermissions;
    }

    //保存用户权限分配
    @Override
    public boolean savePermission(String roleId, List<SysPermission> permissions) {
        baseMapper.deletePermissionByRoleId(roleId);
        if (permissions == null || permissions.isEmpty()){
            return true;
        }

        // 3. 批量插入新权限
        long insertCount = baseMapper.savePermission(roleId, permissions);
        // 4. 判断：插入数量必须等于传入的权限数量
        return insertCount == permissions.size();

    }
}
