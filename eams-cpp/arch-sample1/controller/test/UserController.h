#pragma once

/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/08 21:10:30

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
#ifndef _TESTCONTROLLER_H_
#define _TESTCONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class UserController : public oatpp::web::server::api::ApiController {
    API_ACCESS_DECLARE(UserController);

public:
    // 【接口1】用户注册（无需认证）
    API_DEF_ENDPOINT_INFO("用户注册", registerUser, StringJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT(API_M_POST, "/user/register", registerUser,
        BODY_DTO(UserRegisterDTO::Wrapper, dto),
        execRegister(dto));

    // 【接口2】用户登录（无需认证）
    API_DEF_ENDPOINT_INFO("用户登录", login, LoginJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT(API_M_POST, "/user/login", login,
        BODY_DTO(UserLoginDTO::Wrapper, dto),
        execLogin(dto));

    // 【接口3】查询用户列表（需要认证）
    //API_DEF_ENDPOINT_INFO_QUERY_AUTH("查询用户列表", listUsers,
    //    UserQuery, UserPageJsonVO::Wrapper, API_TAG);
    //API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/user/list",
    //    listUsers, UserQuery, execListUsers(query));

    //// 【接口4】查询用户详情（需要认证）
    //API_DEF_ENDPOINT_INFO_AUTH("查询用户详情", getUserDetail,
    //    UserJsonVO::Wrapper, API_TAG,
    //    API_DEF_ADD_QUERY_PARAMS(String, "id", "用户ID", "uuid-123", true););
    //API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/user/detail", getUserDetail,
    //    QUERY(String, id), execGetUserDetail(id));

    // 其他接口定义...

private:
    StringJsonVO::Wrapper execRegister(const UserRegisterDTO::Wrapper& dto);
    LoginJsonVO::Wrapper execLogin(const UserLoginDTO::Wrapper& dto);
    //UserPageJsonVO::Wrapper execListUsers(const UserQuery::Wrapper& query);
    //UserJsonVO::Wrapper execGetUserDetail(const String& id);
};
#endif