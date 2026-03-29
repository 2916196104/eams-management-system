#pragma once
#ifndef _COURSE_DAO_H_
#define _COURSE_DAO_H_

#include "BaseDAO.h"
#include "domain/do/course/CourseDO.h"
#include "domain/query/course/CourseQuery.h"

#include <memory>
#include <string>

using PtrCourseDO = std::shared_ptr<CourseDO>;

class CourseDao : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const CourseQuery::Wrapper& query, SqlParams& params)
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

		if (query->subject_id && !query->subject_id->empty())
		{
			whereSql += " AND subject_id = ?";
			SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->subject_id.getValue("0")));
		}

		if (query->state && !query->state->empty())
		{
			whereSql += " AND state = ?";
			SQLPARAMS_PUSH(params, "i", int32_t, std::stoi(query->state.getValue("0")));
		}

		if (query->lesson_type && !query->lesson_type->empty())
		{
			whereSql += " AND lesson_type = ?";
			SQLPARAMS_PUSH(params, "i", int32_t, std::stoi(query->lesson_type.getValue("0")));
		}

		if (query->bookable && !query->bookable->empty())
		{
			whereSql += " AND bookable = ?";
			SQLPARAMS_PUSH(params, "i", int32_t, std::stoi(query->bookable.getValue("0")));
		}

		if (query->for_sale && !query->for_sale->empty())
		{
			whereSql += " AND for_sale = ?";
			SQLPARAMS_PUSH(params, "i", int32_t, std::stoi(query->for_sale.getValue("0")));
		}

		if (query->recommend && !query->recommend->empty())
		{
			whereSql += " AND recommend = ?";
			SQLPARAMS_PUSH(params, "i", int32_t, std::stoi(query->recommend.getValue("0")));
		}

		if (query->org_id && !query->org_id->empty())
		{
			whereSql += " AND org_id = ?";
			SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->org_id.getValue("0")));
		}

		return whereSql;
	}

public:
	uint64_t count(const CourseQuery::Wrapper& query);
	std::list<CourseDO> selectWithPage(const CourseQuery::Wrapper& query);
	PtrCourseDO selectById(uint64_t id);
	uint64_t insert(const CourseDO& data);
	uint64_t update(const CourseDO& data);
	uint64_t deleteById(uint64_t id);
};

#endif // !_COURSE_DAO_H_
