#pragma once

#include "../GlobalInclude.h"
// UserVO.h
#include OATPP_CODEGEN_BEGIN(DTO)

// 登录响应VO
class LoginVO : public oatpp::DTO {
    DTO_INIT(LoginVO, DTO);
    API_DTO_FIELD_DEFAULT(String, token, "访问令牌");
    API_DTO_FIELD_DEFAULT(Object<UserDTO>, user, "用户信息");
};

class LoginJsonVO : public JsonVO<LoginVO::Wrapper> {
    DTO_INIT(LoginJsonVO, JsonVO<LoginVO::Wrapper>);
};

class UserJsonVO : public JsonVO<UserDTO::Wrapper> {
    DTO_INIT(UserJsonVO, JsonVO<UserDTO::Wrapper>);
};

class UserPageJsonVO : public JsonVO<UserPageDTO::Wrapper> {
    DTO_INIT(UserPageJsonVO, JsonVO<UserPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)