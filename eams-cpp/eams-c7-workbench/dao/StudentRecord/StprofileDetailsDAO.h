#pragma once

#include "BaseDAO.h"
#include "../../domain/query/StudentRecord/StlistQuery.h"
#include "../../domain/do/StudentRecord/stprofiledetails/StprofileDetailsDO.h"
#include "../../domain/query/StudentRecord/StprofileDetailsQuery.h"

class StprofileDetailsDAO :public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const StlistQuery::Wrapper& query, SqlParams& params);
public:
	// 分页查询数据
	std::list<StprofileDetailsViewDO> selectWithPage(const StlistQuery::Wrapper& query);

	uint64_t count(const StlistQuery::Wrapper& query);
};