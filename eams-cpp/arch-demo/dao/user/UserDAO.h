#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/19 14:38:25

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
#ifndef _USERDAO_H_
#define _USERDAO_H_
#include "BaseDAO.h"
#include "domain/do/user/UserDO.h"
#include "domain/dto/user/UserDTO.h"
#include "domain/query/user/UserQuery.h"

/**
 * 用户数据操作类
 */
class UserDAO : public BaseDAO
{
public:
	// 获取数据条数
	uint64_t count(const UserQuery::Wrapper& query);
	// 获取用户列表
	std::list<PtrUserDO> selectAll(const UserQuery::Wrapper& query);
	// 通过编号获取指定用户
	PtrUserDO selectById(const string& id);
};

#endif // !_USERDAO_H_