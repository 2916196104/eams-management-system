package com.zeroone.star.login.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.login.entity.StaffDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

@Mapper
public interface StaffMapper extends BaseMapper<StaffDO> {

    @Select("SELECT id, mobile, name, head_img, org_id, state, deleted " +
            "FROM staff " +
            "WHERE id = #{userId} AND deleted = 0")
    StaffDO selectCurrentUserById(@Param("userId") Long userId);

    @Update("UPDATE staff " +
            "SET password = #{password} " +
            "WHERE id = #{userId} AND deleted = 0")
    int updatePasswordByUserId(@Param("userId") Long userId, @Param("password") String password);
}
