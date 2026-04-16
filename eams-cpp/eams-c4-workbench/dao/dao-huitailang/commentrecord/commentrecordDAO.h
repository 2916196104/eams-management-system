#pragma once
#ifndef COMMENTRECORDDAO_H
#define COMMENTRECORDDAO_H


#include "BaseDAO.h"
#include "../../../domain/do/TeachEvaluationDO.h"
#include "../../../domain/query/huitailang-query/commentrecordquery.h"

class CommentrecordDAO : public BaseDAO
{
private:
	//构建查询条件
	inline std::string queryConditionBuilder(const CommentrecordQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const CommentrecordQuery::Wrapper& query);
	// 分页查询数据
	std::list<CommentrecordViewDO> selectWithPage(const CommentrecordQuery::Wrapper& query);
	
	
};

#endif