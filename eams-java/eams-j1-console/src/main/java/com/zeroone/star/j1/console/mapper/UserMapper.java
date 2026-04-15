package com.zeroone.star.j1.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j1.console.entity.UserDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

/**
 * <p>
 * 家长端用户表 Mapper 接口
 * </p>
 * @author hxb
 */
@Mapper
public interface UserMapper extends BaseMapper<UserDO> {

    /**
     * 根据ID获取家长姓名
     * @param id 用户ID
     * @return 家长姓名
     */
    @Select("SELECT name FROM user WHERE id = #{id}")
    String getNameById(Long id);

    /**
     * 根据ID获取手机号
     * @param id 用户ID
     * @return 手机号
     */
    @Select("SELECT mobile FROM user WHERE id = #{id}")
    String getMobileById(Long id);
}
