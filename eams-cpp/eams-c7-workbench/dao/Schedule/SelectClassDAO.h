#pragma once
#ifndef _SELECTCLASSDAO_H_
#define _SELECTCLASSDAO_H_

#include "BaseDAO.h"
#include "../../domain/do/Schedule/SelectClassDO.h"
#include "../../domain/query/Schedule/SelectClassQuery.h"

class SelectClassDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const SelectClassQuery::Wrapper& query, SqlParams& params);
public:
	//统计数据条数
	uint64_t count(const SelectClassQuery::Wrapper& query);
	// 分页查询数据
	std::list<SelectClassViewDOPtr> selectWithPage(const SelectClassQuery::Wrapper& query, uint32_t pageIndex, uint32_t pageSize);
};

#endif // !SALES_INCOME_STATEMENT_DAO_H