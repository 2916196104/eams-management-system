#include "stdafx.h"
#include "GetStudentCoursesController.h"
#include "service/Mycustomers/MyCustomersService.h"

StudentCoursesPageJsonVO::Wrapper GetStudentCoursesController::executeGetStudentCourses(const Int64& id, const PayloadDTO& payload)
{
	auto query = StudentCourseQuery::createShared();
	query->student_id = id.getValue(0);
	MyCustomersService service;
	auto dto = service.listStudentCourses(query);
	return StudentCoursesPageJsonVO::createCourseResult(dto);
}