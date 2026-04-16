#pragma once
#ifndef _MONTHLYDATADAO_H_
#define _MONTHLYDATADAO_H_

#include "BaseDAO.h"
#include "domain/do/UserRelated/MonthlyDataDO.h"
#include "domain/query/UserRelated/MonthlyDataQuery.h"

class MonthlyDataDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const MonthlyDataQuery::Wrapper& query, SqlParams& params);
public:
	//统计数据条数
	uint64_t count(const MonthlyDataQuery::Wrapper& query);
	// 不分页查询数据
	std::list<MonthlyDataViewDOPtr> selectWithoutPage(const MonthlyDataQuery::Wrapper& query);
};

#endif