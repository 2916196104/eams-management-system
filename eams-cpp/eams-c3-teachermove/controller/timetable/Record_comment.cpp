#include "Record_comment.h"
#include "stdafx.h"
#include "service/timetable/RecordcommentService.h"

EvaluatePageJsonVO::Wrapper Record_comment::execQueryEvaluation(const EvaluationQuery::Wrapper& query)
{
	auto jvo = EvaluatePageJsonVO::createShared();
	RecordCommentService service;
	jvo->success(service.getEvaluationList(query));
	return jvo;
}

EvaluateRspJsonVO::Wrapper Record_comment::execModifyEvaluate(const EvaluationDTO::Wrapper& dto, const PayloadDTO& payload)
{	
	RecordcommentService service;
	return service.modifyEvaluation(dto, payload);
}
