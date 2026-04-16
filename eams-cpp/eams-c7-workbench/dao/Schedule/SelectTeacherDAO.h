#pragma once
#ifndef _SELECTTEACHERDAO_H_
#define _SELECTTEACHERDAO_H_

#include "BaseDAO.h"
#include "../../domain/do/Schedule/SelectTeacherDO.h"
#include "../../domain/query/Schedule/SelectTeacherQuery.h"

class SelectTeacherDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const SelectTeacherQuery::Wrapper& query, SqlParams& params);
public:
	//统计数据条数
	uint64_t count(const SelectTeacherQuery::Wrapper& query);
	// 分页查询数据
	std::list<SelectTeacherViewDOPtr> selectWithPage(const SelectTeacherQuery::Wrapper& query, uint32_t pageIndex, uint32_t pageSize);
};

#endif 