package com.zeroone.star.student.service.impl;

import com.zeroone.star.student.entity.User;
import com.zeroone.star.student.mapper.UserMapper;
import com.zeroone.star.student.service.IUserService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

/**
 * <p>
 * 家长端用户表 服务实现类
 * </p>
 *
 * @author zrt
 * @since 2026-03-16
 */
@Service
public class UserServiceImpl extends ServiceImpl<UserMapper, User> implements IUserService {

}
