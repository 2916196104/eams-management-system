#include "stdafx.h"
#include "CourseRecordController.h"
#include "../../../service/CourseRecord/CourseRecordService.h"

CourseRecordPageJsonVO::Wrapper CourseRecordController::execQueryCourseRecord(const CourseRecordQuery::Wrapper& query)
{
	auto result = CourseRecordService().listAll(query);
	auto jvo = CourseRecordPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}
