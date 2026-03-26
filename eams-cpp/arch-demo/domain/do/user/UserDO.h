#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/12 19:41:36

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
#ifndef _USERDO_H_
#define _USERDO_H_

#include "../DoInclude.h"
#include "../file/FileDO.h"

/**
 * 测试用户数据实体
 */
class UserDO : public BaseDO
{
	// 用户ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 用户昵称
	MYSQL_SYNTHESIZE(string, nickname, Nickname);
	// 用户年龄
	MYSQL_SYNTHESIZE(int, age, Age);
	// 用户身份证号
	MYSQL_SYNTHESIZE(string, idCard, IdCard);
	// 用户头像
	MYSQL_SYNTHESIZE(string, avatar, Avatar);

	// 关联一个文件实体，存储头像文件信息
	CC_SYNTHESIZE(PtrFileDO, file, File);
public:
	UserDO() : BaseDO("sample_user")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("nickname", "s", nickname);
		MYSQL_ADD_FIELD("age", "i", age);
		MYSQL_ADD_FIELD("id_card", "i", idCard);
		MYSQL_ADD_FIELD("avatar", "s", avatar);
	}
};

// 定义一个用户实体的智能指针
typedef std::shared_ptr<UserDO> PtrUserDO;

#endif // !_USERDO_H_