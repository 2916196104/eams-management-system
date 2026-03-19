#include "stdafx.h"
#include "ClassStudentController.h"
#include "service/class/ClassStudentService.h"

ClassStudentListPageJsonVO::Wrapper ClassStudentController::execQueryClassStudentList(const ClassStudentQuery::Wrapper& query)
{
	ClassStudentService service;
	auto vo = ClassStudentListPageJsonVO::createShared();
	vo->success(service.listClassStudents(query));
	return vo;
}

ClassStudentDetailJsonVO::Wrapper ClassStudentController::execQueryClassStudentDetail(const oatpp::UInt64& id)
{
	ClassStudentService service;
	auto vo = ClassStudentDetailJsonVO::createShared();
	auto dto = service.getClassStudentDetail(id.getValue(0));
	if (dto)
		vo->success(dto);
	else
		vo->fail({});
	return vo;
}

ClassStudentCoursePageJsonVO::Wrapper ClassStudentController::execQueryClassStudentCourseList(const ClassStudentCourseQuery::Wrapper& query)
{
	ClassStudentService service;
	auto vo = ClassStudentCoursePageJsonVO::createShared();
	vo->success(service.listClassStudentCourses(query));
	return vo;
}
