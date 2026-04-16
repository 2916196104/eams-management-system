#pragma once


#include"BaseDAO.h"
#include "domain/do/Homework/homeworklist/HomeworkListDO.h"
#include "domain/query/Homework/homeworklist/HomeworkListQuery.h"

class HomeworkListDAO :public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const HomeworkListQuery::Wrapper& query, SqlParams& params);
public:
	// 分页查询数据
	std::list<HomeworkListViewDO> selectWithPage(const HomeworkListQuery::Wrapper& query);
	// 统计数据条数
	uint64_t count(const HomeworkListQuery::Wrapper& query);
};