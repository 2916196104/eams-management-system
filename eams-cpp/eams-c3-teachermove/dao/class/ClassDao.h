#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/24

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
#ifndef _CLASS_DAO_H_
#define _CLASS_DAO_H_

#include "BaseDAO.h"
#include "domain/do/class/ClassDO.h"
#include "domain/query/class/ClassQuery.h"
#include "dao/class/ClassMapper.h"

#include <memory>
#include <string>

typedef std::shared_ptr<ClassDO> PtrClassDO;

class ClassDao : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const ClassQuery::Wrapper& query, SqlParams& params)
	{
		std::string whereSql = " WHERE deleted = 0";
		if (!query)
		{
			return whereSql;
		}

		if (query->teacher_id && !query->teacher_id->empty())
		{
			whereSql += " AND teacher_id = ?";
			SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->teacher_id.getValue("0")));
		}

		if (query->name && !query->name->empty())
		{
			whereSql += " AND name LIKE ?";
			SQLPARAMS_PUSH(params, "s", std::string, "%" + query->name.getValue("") + "%");
		}

		if (query->course_id && !query->course_id->empty())
		{
			whereSql += " AND course_id = ?";
			SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->course_id.getValue("0")));
		}

		if (query->school_id && !query->school_id->empty())
		{
			whereSql += " AND school_id = ?";
			SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->school_id.getValue("0")));
		}

		if (query->org_id && !query->org_id->empty())
		{
			whereSql += " AND org_id = ?";
			SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->org_id.getValue("0")));
		}

		if (query->be_over && !query->be_over->empty())
		{
			whereSql += " AND be_over = ?";
			SQLPARAMS_PUSH(params, "i", int32_t, std::stoi(query->be_over.getValue("0")));
		}

		return whereSql;
	}

public:
	uint64_t count(const ClassQuery::Wrapper& query);
	std::list<ClassDO> selectWithPage(const ClassQuery::Wrapper& query);
	PtrClassDO selectById(uint64_t id);
};

#endif // !_CLASS_DAO_H_