package com.zeroone.star.student.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j4.student.UserQueryDTO;
import com.zeroone.star.project.dto.j4.student.UserUpdateDTO;
import com.zeroone.star.project.dto.j4.student.UserUpdatePwdDTO;
import com.zeroone.star.project.vo.j4.student.UserVO;
import com.zeroone.star.student.entity.User;
import com.baomidou.mybatisplus.extension.service.IService;

public interface UserService extends IService<User> {

    /**
     * 获取账号列表（条件+分页）
     */
    Page<UserVO> listUser(UserQueryDTO query);

    /**
     * 修改账号信息
     */
    void updateUser(UserUpdateDTO dto);

    /**
     * 修改密码
     */
    void updatePassword(UserUpdatePwdDTO dto);
}