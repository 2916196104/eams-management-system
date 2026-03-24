package com.zeroone.star.student.mapper;

import com.zeroone.star.student.entity.User;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;

/**
 * <p>
 * 家长端用户表 Mapper 接口
 * </p>
 *
 * @author gintoki
 * @since 2026-03-23
 */
@Mapper
public interface UserMapper extends BaseMapper<User> {

}
