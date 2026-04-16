#pragma once

#include"BaseDAO.h"
#include "../../domain/dto/StudentRecord/StlistDTO.h"
#include "../../domain/query/StudentRecord/StlistQuery.h"
#include "../../domain/do/StudentRecord/stclassrecord/StclassRecordDO.h"
#include "../../domain/query/StudentRecord/StclassRecordQuery.h"

class StclassRecordDAO :public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const StlistQuery::Wrapper& query, SqlParams& params);
public:
	// 分页查询数据
	std::list<StclassRecordViewDO> selectWithPage(const StlistQuery::Wrapper& query);
	// 统计数据条数
	uint64_t count(const StlistQuery::Wrapper& query);
};