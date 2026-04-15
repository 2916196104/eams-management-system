package com.zeroone.star.oauth2.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.oauth2.entity.User;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface UserMapper extends BaseMapper<User> {

    @Select("SELECT id, mobile AS username, password, org_id, name FROM staff WHERE mobile = #{mobile} AND deleted = 0")
    User selectManagerByMobile(@Param("mobile") String mobile);

    @Select("SELECT id, mobile AS username, password, org_id, name FROM user WHERE mobile = #{mobile}")
    User selectUserByMobile(@Param("mobile") String mobile);
}
