package com.zeroone.star.sys.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.sys.entity.SysRole;
import com.zeroone.star.sys.mapper.SysRoleMapper;
import com.zeroone.star.sys.service.SysRoleService;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 角色表 服务实现类（sys模块）
 * </p>
 */
@Service
public class SysRoleServiceImpl extends ServiceImpl<SysRoleMapper, SysRole> implements SysRoleService {

    @Override
    public List<SysRole> listRoleByUserId(int userId) {
        return baseMapper.selectByUserId(userId);
    }

    @Override
    public List<SysRole> listRoleByMenuPath(String path) {
        return baseMapper.selectByMenuPath(path);
    }
}
