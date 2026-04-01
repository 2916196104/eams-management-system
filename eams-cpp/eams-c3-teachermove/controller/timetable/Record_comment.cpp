#include "Record_comment.h"
#include "stdafx.h"
#include "service/timetable/RecordcommentService.h"

EvaluatePageJsonVO::Wrapper Record_comment::execQueryEvaluation(const EvaluationQuery::Wrapper& query)
{	
	RecordcommentService service;
	return service.queryEvaluation(query);
}

EvaluateRspJsonVO::Wrapper Record_comment::execModifyEvaluate(const EvaluationDTO::Wrapper& dto, const PayloadDTO& payload)
{	
	RecordcommentService service;
	return service.modifyEvaluation(dto, payload);
}
