#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:23:49

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
#ifndef _LISTENINGCARD_DAO_
#define _LISTENINGCARD_DAO_
#include "BaseDAO.h"
#include "../domain/do/cardDO.h"
#include"../domain/do/cardRecordDO.h"
#include"../domain/dto/listening-card/cardDTO.h"


/**
 * 示例表数据库操作实现
 */
class ListeningCardDAO : public BaseDAO
{
private:

public:
	// 通过姓名查询数据
	std::list<cardDO> selectCardByUserId(const string& userId);
};
#endif // !_LISTENINGCARD_DAO_
