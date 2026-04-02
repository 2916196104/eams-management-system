#pragma once

#ifndef _SCORE_SERVICE_
#define _SCORE_SERVICE_

#include "domain/dto/score/scoreDTO.h"
#include "domain/query/score/scorequery.h"

class ScoreService
{
public:
	// 分页查询学生成绩
    ScorePageDTO::Wrapper listAll(const ScoreQuery::Wrapper& query);

};

#endif // !_SCORE_SERVICE_