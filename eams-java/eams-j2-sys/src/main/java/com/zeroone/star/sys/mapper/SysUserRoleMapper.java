package com.zeroone.star.sys.mapper;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j2.sys.Roleperm.RolepermStaffDTO;
import com.zeroone.star.project.dto.j2.sys.Roleperm.RolepermStaffDTO;
import com.zeroone.star.sys.entity.SysUserRole;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * <p>
 * 用户角色 Mapper 接口
 * </p>
 *
 * @author isme
 * @since 2026-03-20
 */
@Mapper
public interface SysUserRoleMapper extends BaseMapper<SysUserRole> {

    Page<RolepermStaffDTO> selectRoleStaffPage(Page<?> page,
                                               @Param("roleId") String roleId,
                                               @Param("name") String name);

    int insertRoleStaff(@Param("roleId") String roleId, @Param("userId") String userId);

    int deleteByRoleIdAndUserId(@Param("roleId") String roleId, @Param("userId") String userId);
}
