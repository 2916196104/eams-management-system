#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/19 15:17:39

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
#ifndef _USERMAPPER_H_
#define _USERMAPPER_H_
#include "Mapper.h"
#include "domain/do/user/UserDO.h"

class UserMapper : public Mapper<PtrUserDO>
{
public:
	PtrUserDO mapper(ResultSet* resultSet) const override
	{
		PtrUserDO userDO = std::make_shared<UserDO>();
		userDO->setId(resultSet->getString("id"));
		userDO->setNickname(resultSet->getString("nickname"));
		userDO->setAge(resultSet->getInt("age"));
		userDO->setIdCard(resultSet->getString("id_card"));
		userDO->setAvatar(resultSet->getString("avatar"));
		// 头像文件信息
		if (userDO->getAvatar() != "")
		{
			PtrFileDO fd = std::make_shared<FileDO>();
			fd->setId(userDO->getAvatar());
			fd->setName(resultSet->getString("name"));
			fd->setSavePath(resultSet->getString("save_path"));
			userDO->setFile(fd);
		}
		return userDO;
	}
};

#endif // !_USERMAPPER_H_