#include "stdafx.h"
#include "StudentController.h"
#include "./service/GradeService.h"


GradeListJsonVO::Wrapper StudentController::executeQueryGrade() {
	
	GradeService gs;
	auto vo = GradeListJsonVO::createShared();
	vo->success(gs.listAllGrade());
	return vo;
}


