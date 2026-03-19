#pragma once


#include "domain/query/UserQuery.h"
#include "domain/dto/UserDto.h"
class UserService {
public:
    // 用户注册
    std::string registerUser(const UserRegisterDTO::Wrapper& dto);
    // 用户登录
    LoginVO::Wrapper login(const UserLoginDTO::Wrapper& dto);
    // 查询用户列表
    //UserPageDTO::Wrapper listUsers(const UserQuery::Wrapper& query);
    //// 查询用户详情
    //UserDTO::Wrapper getUserById(const std::string& id);
    //// 修改用户信息
    //bool updateUser(const UserDTO::Wrapper& dto, const std::string& operatorId);
    //// 删除用户
    //bool deleteUser(const std::string& id);
    //// 修改密码
    //bool changePassword(const std::string& userId, const std::string&
    //    oldPassword, const std::string& newPassword);
};