#pragma once


#include "../GlobalInclude.h"
// UserDTO.h
#include OATPP_CODEGEN_BEGIN(DTO)

// 用户注册DTO
class UserRegisterDTO : public oatpp::DTO {
    DTO_INIT(UserRegisterDTO, DTO);
    API_DTO_FIELD(String, username, "用户名", true, "");
    API_DTO_FIELD(String, password, "密码", true, "");
    API_DTO_FIELD(String, nickname, "昵称", true, "");
    API_DTO_FIELD_DEFAULT(String, email, "邮箱");
    API_DTO_FIELD_DEFAULT(String, phone, "手机号");
};

// 用户登录DTO
class UserLoginDTO : public oatpp::DTO {
    DTO_INIT(UserLoginDTO, DTO);
    API_DTO_FIELD(String, username, "用户名", true, "");
    API_DTO_FIELD(String, password, "密码", true, "");
};

// 用户信息DTO
class UserDTO : public oatpp::DTO {
    DTO_INIT(UserDTO, DTO);
    API_DTO_FIELD_DEFAULT(String, id, "用户ID");
    API_DTO_FIELD_DEFAULT(String, username, "用户名");
    API_DTO_FIELD_DEFAULT(String, nickname, "昵称");
    API_DTO_FIELD_DEFAULT(String, avatar, "头像");
    API_DTO_FIELD_DEFAULT(String, email, "邮箱");
    API_DTO_FIELD_DEFAULT(String, phone, "手机号");
    API_DTO_FIELD_DEFAULT(String, sex, "性别");
    API_DTO_FIELD_DEFAULT(Int32, age, "年龄");
};

// 用户分页DTO
class UserPageDTO : public PageDTO<UserDTO::Wrapper> {
    DTO_INIT(UserPageDTO, PageDTO<UserDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)