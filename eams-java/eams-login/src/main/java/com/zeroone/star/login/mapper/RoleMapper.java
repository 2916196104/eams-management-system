package com.zeroone.star.login.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.login.entity.RoleDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface RoleMapper extends BaseMapper<RoleDO> {

    @Select("SELECT DISTINCT sr.code " +
            "FROM sys_role sr " +
            "INNER JOIN sys_user_role sur ON sr.id = sur.role_id " +
            "WHERE sur.user_id = #{userId} " +
            "ORDER BY sr.id")
    List<String> selectRoleCodesByUserId(@Param("userId") Long userId);
}
