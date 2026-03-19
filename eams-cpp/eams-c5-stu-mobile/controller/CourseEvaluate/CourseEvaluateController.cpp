#include "stdafx.h"
#include "CourseEvaluateController.h"

StringJsonVO::Wrapper CourseEvaluateController::ExecuteCourseTest(const PageQuery::Wrapper& query) {
	// 创建一个响应结果
	auto vo = StringJsonVO::createShared();
	vo->success(ZH_WORDS_GETTER("CourseEvalute.resp"));
	return vo;
}
