#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/14 19:15:19

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _AUTHDTO_H_
#define _AUTHDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 数据传输对象
 */

// 发送验证码传输对象
class SendResetCodeDTO : public oatpp::DTO
{
    DTO_INIT(SendResetCodeDTO, oatpp::DTO);

    API_DTO_FIELD_REQUIRE(String, mobile, ZH_WORDS_GETTER("login.field.mobile"), true);
    API_DTO_FIELD_REQUIRE(String, email, ZH_WORDS_GETTER("login.field.email"), true);
};

// 发送验证码结果传输对象
class SendResetCodeRespDTO : public oatpp::DTO
{
    DTO_INIT(SendResetCodeRespDTO, oatpp::DTO);
    API_DTO_FIELD_DEFAULT(Boolean, sendResult, ZH_WORDS_GETTER("login.send.success"));
    API_DTO_FIELD_DEFAULT(String, msg, ZH_WORDS_GETTER("login.send.msg")); // 300秒
};

// 修改密码传输对象
class UpdatePasswordDTO : public oatpp::DTO
{
    DTO_INIT(UpdatePasswordDTO, oatpp::DTO);

    API_DTO_FIELD_REQUIRE(String, mobile, ZH_WORDS_GETTER("login.field.mobile"), true);
    API_DTO_FIELD_REQUIRE(String, email, ZH_WORDS_GETTER("login.field.email"), true);
    API_DTO_FIELD_REQUIRE(String, verifyCode, ZH_WORDS_GETTER("login.field.verify-code"), true);
    API_DTO_FIELD_REQUIRE(String, newPassword, ZH_WORDS_GETTER("login.field.new-password"), true);
};

// 修改密码结果传输对象
class UpdatePasswordRespDTO : public oatpp::DTO
{
    DTO_INIT(UpdatePasswordRespDTO, oatpp::DTO);
    API_DTO_FIELD_DEFAULT(Boolean, updateResult, ZH_WORDS_GETTER("login.update.success"));
    API_DTO_FIELD_DEFAULT(String, msg, ZH_WORDS_GETTER("login.update.msg")); // 300秒
};


// 发送注册验证码传输对象
class SendRegisterCodeDTO : public oatpp::DTO
{
    DTO_INIT(SendRegisterCodeDTO, oatpp::DTO);

    API_DTO_FIELD_REQUIRE(String, mobile, ZH_WORDS_GETTER("login.field.mobile"), true);
    API_DTO_FIELD_REQUIRE(String, email, ZH_WORDS_GETTER("login.field.email"), true);
};

// 发送验证码结果传输对象
class SendRegisterCodeRespDTO : public oatpp::DTO
{
    DTO_INIT(SendRegisterCodeRespDTO, oatpp::DTO);
    API_DTO_FIELD_DEFAULT(Boolean, sendResult, ZH_WORDS_GETTER("login.send.success"));
    API_DTO_FIELD_DEFAULT(String, msg, ZH_WORDS_GETTER("login.register.msg")); // 300秒
};


// 注册账号传输对象
class RegisterDTO : public oatpp::DTO
{
    DTO_INIT(RegisterDTO, oatpp::DTO);

    API_DTO_FIELD_REQUIRE(String, mobile, ZH_WORDS_GETTER("login.field.mobile"), true);
    API_DTO_FIELD_REQUIRE(String, email, ZH_WORDS_GETTER("login.field.email"), true);
    API_DTO_FIELD_REQUIRE(String, verifyCode, ZH_WORDS_GETTER("login.field.verify-code"), true);
    API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("login.field.name"), true);
    API_DTO_FIELD_REQUIRE(String, password, ZH_WORDS_GETTER("login.field.password"), true);
};
// 注册账号结果传输对象
class RegisterRespDTO : public oatpp::DTO
{
    DTO_INIT(RegisterRespDTO, oatpp::DTO);
    API_DTO_FIELD_DEFAULT(Boolean, registerResult, ZH_WORDS_GETTER("login.register.success"));
    API_DTO_FIELD_DEFAULT(String, msg, ZH_WORDS_GETTER("login.register.msg")); // 300秒
};



#include OATPP_CODEGEN_END(DTO)

#endif // !_AUTHDTO_H_