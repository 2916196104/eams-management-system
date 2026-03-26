package com.zeroone.star.sys.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.sys.entity.SysRole;

import java.util.List;

/**
 * <p>
 * 角色表 服务接口（sys模块）
 * </p>
 */
public interface SysRoleService extends IService<SysRole> {
    List<SysRole> listRoleByUserId(int userId);

    List<SysRole> listRoleByMenuPath(String path);
}
