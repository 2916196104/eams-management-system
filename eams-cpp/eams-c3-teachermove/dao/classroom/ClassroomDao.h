#pragma once
#ifndef _CLASSROOM_DAO_H_
#define _CLASSROOM_DAO_H_

#include "BaseDAO.h"
#include "domain/do/classroom/ClassroomDO.h"
#include "domain/query/classroom/ClassroomQuery.h"

#include <memory>
#include <string>

using PtrClassroomDO = std::shared_ptr<ClassroomDO>;

class ClassroomDao : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const ClassroomQuery::Wrapper& query, SqlParams& params)
	{
		std::string whereSql = " WHERE deleted = 0";
		if (!query)
		{
			return whereSql;
		}

		if (query->name && !query->name->empty())
		{
			whereSql += " AND name LIKE ?";
			SQLPARAMS_PUSH(params, "s", std::string, "%" + query->name.getValue("") + "%");
		}

		if (query->address && !query->address->empty())
		{
			whereSql += " AND address LIKE ?";
			SQLPARAMS_PUSH(params, "s", std::string, "%" + query->address.getValue("") + "%");
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

		return whereSql;
	}

public:
	uint64_t count(const ClassroomQuery::Wrapper& query);
	std::list<ClassroomDO> selectWithPage(const ClassroomQuery::Wrapper& query);
	PtrClassroomDO selectById(uint64_t id);
	uint64_t insert(const ClassroomDO& data);
	uint64_t update(const ClassroomDO& data);
	uint64_t deleteById(uint64_t id);
};

#endif // !_CLASSROOM_DAO_H_
