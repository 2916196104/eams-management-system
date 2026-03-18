#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/01 17:39:36

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
#ifndef _USERCONTROLLER_H_
#define _USERCONTROLLER_H_
#include "domain/query/user/UserQuery.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/user/UserVO.h"
#include "domain/vo/user/MenuVO.h"
using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("user.tag")

class UserController : public oatpp::web::server::api::ApiController
{
	// 添加访问定义
	API_ACCESS_DECLARE(UserController);
public:
	// 定义查询所有用户信息接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("user.query-all.summary"), queryAllUser, UserQuery, UserPageJsonVO::Wrapper, API_TAG);
	// 定义查询所有用户信息接口端点
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/user/query-all", queryAllUser, UserQuery, executeQueryAll(query));

	// 定义获取用户详细信息接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("user.query-one.summary"), queryOneUser, UserDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("user.field.id"), "ae65c714d48d4f34b52479f5482c0edd", true);
	);
	// 定义获取用户详细信息接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/user/query-one", queryOneUser, QUERY(String, id), executeQueryOne(id));

	// 定义新增用户信息接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("user.add-user.summary"), addUser, StringJsonVO::Wrapper, API_TAG);
	// 定义新增用户信息接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/user/add-user", addUser, BODY_DTO(UserAddDTO::Wrapper, dto), executeAddUser(dto));

	// 定义新增收货地址接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("address.add-address.summary"), addUserAddr, StringJsonVO::Wrapper, API_TAG);
	// 定义新增收货地址接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/user/add-user-addr", addUserAddr, BODY_DTO(AddressAddDTO::Wrapper, dto), executeAddUserAddr(dto));

	// 定义查询用户菜单接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("user.query-menu.summary"), queryMenu, MenuJsonVO::Wrapper, API_TAG);
	// 定义查询用户菜单接口端点
	API_HANDLER_ENDPOINT_NOPARAM_AUTH(API_M_GET, "/user/query-menu", queryMenu, executeQueryMenu(authObject->getPayload()));
private:
	// 查询所有
	UserPageJsonVO::Wrapper executeQueryAll(const UserQuery::Wrapper& userQuery);
	// 查询详情
	UserDetailJsonVO::Wrapper executeQueryOne(const String& id);
	// 新增用户信息
	StringJsonVO::Wrapper executeAddUser(const UserAddDTO::Wrapper& dto);
	// 新增用户地址
	StringJsonVO::Wrapper executeAddUserAddr(const AddressAddDTO::Wrapper& dto);
	// 测试菜单
	MenuJsonVO::Wrapper executeQueryMenu(const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif // _USERCONTROLLER_H_