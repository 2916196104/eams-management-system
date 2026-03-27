package com.zeroone.star.login.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.login.entity.RoleDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface RoleMapper extends BaseMapper<RoleDO> {

    @Select("SELECT role_info.code " +
            "FROM (" +
            "    SELECT DISTINCT sr.id, sr.code " +
            "    FROM sys_role sr " +
            "    INNER JOIN sys_user_role sur ON sr.id = sur.role_id " +
            "    WHERE sur.user_id = #{userId}" +
            ") role_info " +
            "ORDER BY role_info.id")
    List<String> selectRoleCodesByUserId(@Param("userId") Long userId);

    @Select("SELECT permission_info.code " +
            "FROM (" +
            "    SELECT DISTINCT sp.id, sp.code " +
            "    FROM sys_permission sp " +
            "    INNER JOIN sys_role_permission srp ON sp.id = srp.permission_id " +
            "    INNER JOIN sys_user_role sur ON srp.role_id = sur.role_id " +
            "    WHERE sur.user_id = #{userId} " +
            "      AND sp.enabled = 1 " +
            "      AND sp.code IS NOT NULL " +
            "      AND sp.code <> ''" +
            ") permission_info " +
            "ORDER BY permission_info.id")
    List<String> selectPermissionCodesByUserId(@Param("userId") Long userId);
}
