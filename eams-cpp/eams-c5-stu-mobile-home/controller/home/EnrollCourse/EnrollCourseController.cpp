

#include "stdafx.h"
#include "EnrollCourseController.h"
#include "../../../service/home/EnrollCourse/EnrollCourseService.h"

EnrollCoursePageJsonVO::Wrapper EnrollCourseController::executeQueryEnrollCourse(const EnrollCourseQuery::Wrapper & query)
{
	auto result = EnrollCourseService().listAll(query);
	auto jvo = EnrollCoursePageJsonVO::createShared();

	jvo->success(result);
	return jvo;
}