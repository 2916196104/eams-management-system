#pragma once

#ifndef __RECORDCOMMENT_SERVICE_H__
#define __RECORDCOMMENT_SERVICE_H__

#include "domain/query/timetable/TimetableQuery.h"
#include "domain/dto/timetable/TimetableDTO.h"
#include "domain/vo/timetable/TimetableVO.h"

class RecordcommentService
{
public:
	EvaluatePageJsonVO::Wrapper queryEvaluation(const EvaluationQuery::Wrapper& query);
	EvaluateRspJsonVO::Wrapper modifyEvaluation(const EvaluationDTO::Wrapper& dto, const PayloadDTO& payload);
};

#endif // __RECORDCOMMENT_SERVICE_H__
