/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/31 17:32:33

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
#include "stdafx.h"
#include "MenuDAO.h"
#include "MenuMapper.h"

std::list<PtrMenuDO> MenuDAO::selectAll()
{
	string sql = "select id,text,icon,href,parent_id from sample_menu";
	return sqlSession->executeQuery<PtrMenuDO>(sql, MenuMapper());
}
