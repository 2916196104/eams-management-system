#include "stdafx.h"
#include "StudentController.h"


PointPageJsonVO::Wrapper StudentController::executeQueryPoint(const PointQuery::Wrapper & query)
{
	UserService us;
	auto vo = UserPageJsonVO::createShared();
	vo->success(us.listAll(query));
	return vo;
}









