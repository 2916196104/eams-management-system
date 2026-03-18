#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/31 19:50:33

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
#ifndef _MENUMAPPER_H_
#define _MENUMAPPER_H_
#include "Mapper.h"
#include "domain/do/user/MenuDO.h"

class MenuMapper : public Mapper<PtrMenuDO>
{
public:
	PtrMenuDO mapper(ResultSet* resultSet) const override
	{
		auto md = std::make_shared<MenuDO>();
		md->setId(resultSet->getString("id"));
		md->setText(resultSet->getString("text"));
		md->setIcon(resultSet->getString("icon"));
		md->setHref(resultSet->getString("href"));
		md->setParentId(resultSet->getString("parent_id"));
		return md;
	}
};

#endif // !_MENUMAPPER_H_