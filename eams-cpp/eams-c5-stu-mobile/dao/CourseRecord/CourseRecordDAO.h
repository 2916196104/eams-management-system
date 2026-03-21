#pragma once
#ifndef _COURSERECORD_DAO_H_
#define _COURSERECORD_DAO_H_

#include "BaseDAO.h"
#include "../../domain/do/CourseRecordDO.h"
#include "../../domain/query/CourseRecord/CourseRecordQuery.h"

class CourseRecordDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const CourseRecordQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const CourseRecordQuery::Wrapper& query);
	// 分页查询数据
	std::list<CourseRecordDO> selectWithPage(const CourseRecordQuery::Wrapper& query);
};

#endif // !_COURSERECORD_DAO_H_
