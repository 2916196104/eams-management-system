#pragma once
#ifndef ROLLCALLRECORDDAO_H
#define ROLLCALLRECORDDAO_H


#include "BaseDAO.h"
#include "../../../domain/do/LessonStudentDO.h"
#include "../../../domain/query/huitailang-query/rollcallquery.h"

class RollcallrecordDAO : public BaseDAO
{
private:
	//构建查询条件
	inline std::string queryConditionBuilder(const RollcallQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const RollcallQuery::Wrapper& query);
	// 分页查询数据
	std::list<RollcallrecordViewDO> selectWithPage(const RollcallQuery::Wrapper& query);


};

#endif