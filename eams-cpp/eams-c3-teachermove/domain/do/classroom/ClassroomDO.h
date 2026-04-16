#pragma once
/*
 Copyright Zero One Star. All rights reserved.

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
#ifndef _CLASSROOM_DO_H_
#define _CLASSROOM_DO_H_

#include "BaseDO.h"
#include "SqlHelper.h"

/**
 * 教室表 DO（对应 classroom 表）
 */
class ClassroomDO : public BaseDO
{
public:
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(std::string, name, Name);
	MYSQL_SYNTHESIZE(std::string, address, Address);
	MYSQL_SYNTHESIZE(int32_t, area, Area);
	MYSQL_SYNTHESIZE(std::string, remark, Remark);
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	MYSQL_SYNTHESIZE(int64_t, editor, Editor);
	MYSQL_SYNTHESIZE(std::string, addTime, AddTime);
	MYSQL_SYNTHESIZE(std::string, editTime, EditTime);
	MYSQL_SYNTHESIZE(bool, deleted, Deleted);
	MYSQL_SYNTHESIZE(int64_t, schoolId, SchoolId);
	MYSQL_SYNTHESIZE(int64_t, orgId, OrgId);

public:
	ClassroomDO() : BaseDO("classroom")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("address", "s", address);
		MYSQL_ADD_FIELD("area", "i", area);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("creator", "ll", creator);
		MYSQL_ADD_FIELD("editor", "ll", editor);
		MYSQL_ADD_FIELD("add_time", "dt", addTime);
		MYSQL_ADD_FIELD("edit_time", "dt", editTime);
		MYSQL_ADD_FIELD("deleted", "b", deleted);
		MYSQL_ADD_FIELD("school_id", "ll", schoolId);
		MYSQL_ADD_FIELD("org_id", "ll", orgId);
	}
};

#endif // !_CLASSROOM_DO_H_
