package com.zeroone.star.oauth2.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.oauth2.entity.User;

public interface IUserService extends IService<User> {

    User getManagerByMobile(String mobile);

    User getUserByMobile(String mobile);
}
