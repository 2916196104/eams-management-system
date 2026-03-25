#include "stdafx.h"
#include "StudentController.h"
#include "./service/GradeService.h"


GradePageJsonVO::Wrapper StudentController::executeQueryGrade(const GradeQuery::Wrapper& query) {
	GradeService gs;
	auto vo = GradePageJsonVO::createShared();
	vo->success(gs.listAllGrade(query));
	return vo;
}

#include "./domain/vo/PointPageJsonVO.h"
#include "./domain/query/PointQuery.h"
#include "./service/PointService.h"
PointPageJsonVO::Wrapper StudentController::executeQueryPoint(const PointQuery::Wrapper & query)
{
	PointService ps;
	auto vo = PointPageJsonVO::createShared();
	vo->success(ps.listAll(query));
	return vo;
}

