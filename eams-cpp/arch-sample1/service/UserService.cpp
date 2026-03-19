// UserService.cpp

#include "stdafx.h"
#include "UserService.h"
#include "id/UuidFacade.h"
#include "dao/Userdao.h"

// 放到最后导入防止编译冲突
#include "NacosClient.h"


std::string UserService::registerUser(const UserRegisterDTO::Wrapper& dto) {
    // 【步骤1】检查用户名是否已存在
    UserDAO dao;
    auto existUser = dao.selectByUsername(dto->username.getValue(""));
    if (existUser) {
        throw std::runtime_error("用户名已存在");
    }

    // 【步骤2】密码加密
    BcryptHelper bcrypt;
    std::string hashedPassword = bcrypt.hash(dto->password.getValue(""));

    // 【步骤3】DTO转DO
    UserDO user;
    ZO_STAR_DOMAIN_DTO_TO_DO(user, dto,
        Username, username,
        Nickname, nickname,
        Email, email,
        Phone, phone
    );
    user.setPassword(hashedPassword);
    user.setId(UuidFacade().genUuid());
    user.setStatus(1);  // 默认启用
    user.setCreateTime(SimpleDateTimeFormat::format());

    // 【步骤4】保存到数据库
    if (dao.insert(user) != 1) {
        throw std::runtime_error("用户注册失败");
    }

    // 【步骤5】发送欢迎邮件（异步）
    if (user.getEmail() != "") {
        ZO_CREATE_MAIL_SENDER(emailSender);
        emailSender.sendTextMail(
            user.getEmail(),
            "欢迎注册",
            "尊敬的 " + user.getNickname() + "，欢迎注册我们的服务！"
        );
    }

    return user.getId();
}

LoginVO::Wrapper UserService::login(const UserLoginDTO::Wrapper& dto) {
    // 【步骤1】查询用户
    UserDAO dao;
    auto user = dao.selectByUsername(dto->username.getValue(""));
    if (!user) {
        throw std::runtime_error("用户名或密码错误");
    }

    // 【步骤2】验证密码
    BcryptHelper bcrypt;
    if (!bcrypt.verify(dto->password.getValue(""), user->getPassword())) {
        throw std::runtime_error("用户名或密码错误");
    }

    // 【步骤3】检查状态
    if (user->getStatus() != 1) {
        throw std::runtime_error("用户已被禁用");
    }

    // 【步骤4】生成JWT Token
    jwt::jwt_object obj{
        jwt::params::algorithm("HS256"),
        jwt::params::secret("your-secret-key"),
        jwt::params::payload({
            {"userId", user->getId()},
            {"username", user->getUsername()},
            {"exp", std::chrono::system_clock::now() + std::chrono::hours(24)}
        })
    };
    std::string token = obj.signature();

    // 【步骤5】缓存登录信息到Redis
    ZO_CREATE_REDIS_CLIENT(redis);
    redis.hset("user:" + user->getId(), "token", token);
    redis.hset("user:" + user->getId(), "loginTime",
        SimpleDateTimeFormat::format());
    redis.expire("user:" + user->getId(), std::chrono::hours(24));

    // 【步骤6】构造返回数据
    auto loginVO = LoginVO::createShared();
    loginVO->token = token;

    auto userDTO = UserDTO::createShared();
    ZO_STAR_DOMAIN_DO_TO_DTO_1(userDTO, user,
        id, Id,
        username, Username,
        nickname, Nickname,
        avatar, Avatar,
        email, Email,
        phone, Phone,
        sex, Sex,
        age, Age
    );
    loginVO->user = userDTO;

    return loginVO;
}