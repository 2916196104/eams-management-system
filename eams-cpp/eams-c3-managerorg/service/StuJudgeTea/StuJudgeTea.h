#pragma once
#ifndef _STUJUDGETEA_SERVICE_
#define _STUJUDGETEA_SERVICE_
#include "domain/query/StuJudgeTea/StuJudgeTeaQuery.h"
#include "domain/dto/StuJudgeTea/StuJudgeTeaDTO.h"

/**
 * 学评教服务实现
 */
class StuJudgeTeaService
{
public:
	// 分页查询所有数据
	StuJudgeTeaPageDTO::Wrapper listAll(const StuJudgeTeaQuery::Wrapper& query);
};

#endif // !_STUJUDGETEA_SERVICE_
