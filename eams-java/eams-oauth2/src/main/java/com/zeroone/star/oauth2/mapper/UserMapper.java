package com.zeroone.star.oauth2.mapper;


import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.oauth2.entity.User;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

/**
 * <p>
 * 用户表 Mapper 接口
 * </p>
 * @author 阿伟
 */
@Mapper
public interface UserMapper extends BaseMapper<User> {

    /**
     * 根据手机号查询员工信息（用于登录）
     * @param mobile 手机号
     * @return 用户信息
     */
    @Select("SELECT id, mobile AS username, password, org_id, name FROM staff WHERE mobile = #{mobile} AND deleted = 0")
    User selectByMobile(@Param("mobile") String mobile);
}