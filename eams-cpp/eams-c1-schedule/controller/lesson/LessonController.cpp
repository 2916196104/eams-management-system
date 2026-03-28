#include "stdafx.h"
#include "LessonController.h"
#include "service/lesson/LessonService.h"

LessonPageJsonVO::Wrapper LessonController::execListLesson(const LessonQuery::Wrapper& query, const PayloadDTO& payload)
{
	// 实例化 Service
	LessonService service;
	auto resultPage = service.listLesson(query, payload);

	// 构造返回对象
	auto jvo = LessonPageJsonVO::createShared();
	jvo->success(resultPage); 
	return jvo;
}

// 参数改为 Int64 lessonId，而不是 DTO
StringJsonVO::Wrapper LessonController::execSignLesson(const Int64& lessonId, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();

	// 参数校验
	if (!lessonId || lessonId <= 0) {
		jvo->init("lessonId invalidate.", RS_PARAMS_INVALID);
		return jvo;
	}

	// 调用 Service
	LessonService service;
	bool isSuccess = service.signLesson(lessonId.getValue(0), payload);

	if (isSuccess) {
		jvo->success(ZH_WORDS_GETTER("lesson.sign.success"));
	}
	else {
		jvo->fail(ZH_WORDS_GETTER("lesson.sign.fail"));
	}

	return jvo;
}