#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/19 16:18:58

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
#ifndef _USERSERVICE_H_
#define _USERSERVICE_H_
#include "domain/query/user/UserQuery.h"
#include "domain/dto/user/UserDTO.h"

/**
 * 用户业务逻辑类
 */
class UserService
{
private:
	// 获取文件服务器地址
	inline string getDfsServerAddrssUrl();
public:
	// 查询所有用户
	UserPageDTO::Wrapper listAll(const UserQuery::Wrapper& query);
	// 添加用户
	std::string saveUser(const UserAddDTO::Wrapper& dto);
	// 获取用户详情
	UserDetailDTO::Wrapper getUserDetail(const oatpp::String& id);
};

#endif // !_USERSERVICE_H_