package com.zeroone.star.sys.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.sys.entity.SysRole;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

/**
 * <p>
 * 角色 Mapper 接口
 * </p>
 *
 * @author isme
 * @since 2026-03-23
 */
@Mapper
public interface SysRoleMapper extends BaseMapper<SysRole> {
    List<SysRole> selectByUserId(int userId);

    List<SysRole> selectByMenuPath(String path);
}
