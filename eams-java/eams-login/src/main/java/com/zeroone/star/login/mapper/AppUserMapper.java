package com.zeroone.star.login.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.login.entity.AppUserDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

@Mapper
public interface AppUserMapper extends BaseMapper<AppUserDO> {

    @Select("SELECT id, mobile, name, org_id, state FROM user WHERE id = #{userId}")
    AppUserDO selectCurrentUserById(@Param("userId") Long userId);

    @Update("UPDATE user SET password = #{password} WHERE id = #{userId}")
    int updatePasswordByUserId(@Param("userId") Long userId, @Param("password") String password);
}
