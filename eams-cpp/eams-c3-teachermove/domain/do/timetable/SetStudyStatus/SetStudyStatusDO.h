#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/02/17 16:25:30

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
#ifndef _SETSTUDYSTATUSDO_H_
#define _SETSTUDYSTATUSDO_H_
#include "../../DoInclude.h"

/**
 * 测试菜单数据库实体
 */
class StatusDO : public BaseDO
{
	// 唯一编号
	MYSQL_SYNTHESIZE(string, id, Id);
	// 签到时间
	MYSQL_SYNTHESIZE(string, time, Time);
	// 签到方式
	MYSQL_SYNTHESIZE(int, type, Type);
	// 签到结果
	MYSQL_SYNTHESIZE(int, state, State);
	
public:
	StatusDO() : BaseDO("lesson_student")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("time", "s", time);
		MYSQL_ADD_FIELD("type", "i", type);
		MYSQL_ADD_FIELD("state", "i", state);
	}

};



#endif // !_SETSTUDYSTATUSDO_H_