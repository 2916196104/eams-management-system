#include "stdafx.h"
#include "StudentController.h"



GradeJsonVO::Wrapper StudentController::executeQueryGrade(const GradeQuery::Wrapper& query) {
	auto data = GradeDTO::createShared();
	auto vo = GradeJsonVO::createShared();
	vo->success(data);
	return vo;
}


