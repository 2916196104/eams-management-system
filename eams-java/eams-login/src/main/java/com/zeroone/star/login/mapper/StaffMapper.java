package com.zeroone.star.login.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.login.entity.StaffDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface StaffMapper extends BaseMapper<StaffDO> {

    @Select("SELECT id, mobile, name, org_id, state, deleted " +
            "FROM staff " +
            "WHERE id = #{userId} AND deleted = 0")
    StaffDO selectCurrentUserById(@Param("userId") Long userId);
}
