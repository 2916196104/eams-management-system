#pragma once

#ifndef __RECORDCOMMENT_SERVICE_H__
#define __RECORDCOMMENT_SERVICE_H__

#include "domain/GlobalInclude.h"
#include "domain/query/timetable/TimetableQuery.h"
#include "domain/dto/timetable/TimetableDTO.h"

class RecordCommentService
{
public:
	EvaluatePageDTO::Wrapper getEvaluationList(const EvaluationQuery::Wrapper& query);
};

class RecordcommentService
{
public:
	EvaluatePageJsonVO::Wrapper queryEvaluation(const EvaluationQuery::Wrapper& query);
	EvaluateRspJsonVO::Wrapper modifyEvaluation(const EvaluationDTO::Wrapper& dto, const PayloadDTO& payload);
};

#endif
