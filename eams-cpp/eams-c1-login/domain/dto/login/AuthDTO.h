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

class SendResetCodeDTO : public oatpp::DTO
{
    DTO_INIT(SendResetCodeDTO, oatpp::DTO);

    API_DTO_FIELD_REQUIRE(String, mobile, ZH_WORDS_GETTER("login.field.mobile"), true);
    API_DTO_FIELD_REQUIRE(String, email, ZH_WORDS_GETTER("login.field.email"), true);
};


class SendResetCodeRespDTO : public oatpp::DTO
{
    DTO_INIT(SendResetCodeRespDTO, oatpp::DTO);

    API_DTO_FIELD_DEFAULT(String, mobile, ZH_WORDS_GETTER("login.field.mobile"));
    API_DTO_FIELD_DEFAULT(String, email, ZH_WORDS_GETTER("login.field.email"));
    API_DTO_FIELD_DEFAULT(Int32, expireSeconds, ZH_WORDS_GETTER("login.field.expire-seconds")); // 300秒
};



class ResetPasswordDTO : public oatpp::DTO
{
    DTO_INIT(ResetPasswordDTO, oatpp::DTO);

    API_DTO_FIELD_REQUIRE(String, mobile, ZH_WORDS_GETTER("login.field.mobile"), true);
    API_DTO_FIELD_REQUIRE(String, email, ZH_WORDS_GETTER("login.field.email"), true);
    API_DTO_FIELD_REQUIRE(String, verifyCode, ZH_WORDS_GETTER("login.field.verify-code"), true);
    API_DTO_FIELD_REQUIRE(String, newPassword, ZH_WORDS_GETTER("login.field.new-password"), true);
};

class ResetPasswordRespDTO : public oatpp::DTO
{
    DTO_INIT(ResetPasswordRespDTO, oatpp::DTO);

    API_DTO_FIELD_DEFAULT(Boolean, success, ZH_WORDS_GETTER("login.reset.success"));
    API_DTO_FIELD_DEFAULT(String, mobile, ZH_WORDS_GETTER("login.reset.mobile"));
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_AUTHDTO_H_