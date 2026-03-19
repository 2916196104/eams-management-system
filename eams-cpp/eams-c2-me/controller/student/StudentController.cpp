#include "stdafx.h"
#include "StudentController.h"
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









