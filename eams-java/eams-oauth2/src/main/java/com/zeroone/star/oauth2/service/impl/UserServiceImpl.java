package com.zeroone.star.oauth2.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.oauth2.entity.User;
import com.zeroone.star.oauth2.mapper.UserMapper;
import com.zeroone.star.oauth2.service.IUserService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

@Service
public class UserServiceImpl extends ServiceImpl<UserMapper, User> implements IUserService {

    @Resource
    private UserMapper userMapper;

    @Override
    public User getManagerByMobile(String mobile) {
        return userMapper.selectManagerByMobile(mobile);
    }

    @Override
    public User getUserByMobile(String mobile) {
        return userMapper.selectUserByMobile(mobile);
    }
}
