#include "stdafx.h"
#include "CourseEvaluateController.h"
#include "../../service/CourseEvaluate/CourseEvaluateService.h"

CourseEvaluatePageJsonVO::Wrapper CourseEvaluateController::execQueryCourseEvaluate(const CourseEvaluateQuery::Wrapper& query)
{
	auto result = CourseEvaluateService().listAll(query);
	auto jvo = CourseEvaluatePageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

StringJsonVO::Wrapper CourseEvaluateController::execAddCourseEvaluate(const CourseEvaluateDTO::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();
	// 参数校验
	if (!dto->course_id || !dto->content || !dto->score)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// 传递 payload
	dto->setPayload(&payload);
	// 执行保存
	uint64_t id = CourseEvaluateService().saveData(dto);
	if (id > 0)
		jvo->success(std::to_string(id));
	else
		jvo->fail(nullptr);
	return jvo;
}
