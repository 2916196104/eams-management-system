#include "stdafx.h"
#include "CourseRecordController.h"

StringJsonVO::Wrapper CourseRecordController::ExecuteCourseTest(const PageQuery::Wrapper& query) {
	// 创建一个响应结果
	auto vo = StringJsonVO::createShared();
	vo->success(ZH_WORDS_GETTER("CourseRecord.resp"));
	return vo;
}
