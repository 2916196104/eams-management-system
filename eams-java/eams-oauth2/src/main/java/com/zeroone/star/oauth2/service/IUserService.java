package com.zeroone.star.oauth2.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.oauth2.entity.User;

/**
 * <p>
 * 用户表 服务类
 * </p>
 * @author 阿伟
 */
public interface IUserService extends IService<User> {

    /**
     * 根据手机号查询用户
     * @param mobile 手机号
     * @return 用户信息
     */
    User getByMobile(String mobile);

}
