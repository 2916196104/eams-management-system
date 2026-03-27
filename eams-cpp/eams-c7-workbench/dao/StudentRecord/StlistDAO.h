#pragma once

#include "BaseDAO.h"
#include "../../domain/do/StudentRecord/stlist/StlistDO.h"
#include "../../domain/query/StudentRecord/StlistQuery.h"

class StlistDAO :public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const StlistQuery::Wrapper& query, SqlParams& params);
public:
	// 分页查询数据
	std::list<StlistViewDO> selectWithPage(const StlistQuery::Wrapper& query);
	// 统计数据条数
	uint64_t count(const StlistQuery::Wrapper& query);
};