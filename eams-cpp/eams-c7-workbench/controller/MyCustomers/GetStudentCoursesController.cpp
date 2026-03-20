#include "stdafx.h"
#include "GetStudentCoursesController.h"

StudentCoursesPageJsonVO::Wrapper GetStudentCoursesController::executeGetStudentCourses(const String& name, const PayloadDTO& payload)
{
	auto vo = StudentCoursesPageJsonVO::createShared();
	return vo;
}