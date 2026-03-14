package com.zeroone.star.stumanager.service.impl;

import com.zeroone.star.stumanager.entity.User;
import com.zeroone.star.stumanager.mapper.UserMapper;
import com.zeroone.star.stumanager.service.IUserService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

/**
 * <p>
 * 家长端用户表 服务实现类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Service
public class UserServiceImpl extends ServiceImpl<UserMapper, User> implements IUserService {

}
