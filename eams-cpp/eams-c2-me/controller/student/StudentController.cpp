#include "stdafx.h"
#include "StudentController.h"
#include "./service/GradeService.h"


GradePageJsonVO::Wrapper StudentController::executeQueryGrade(const GradeQuery::Wrapper& query) {
	GradeService gs;
	auto vo = GradePageJsonVO::createShared();
	vo->success(gs.listAllGrade(query));
	return vo;
}

