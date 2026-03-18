#include "stdafx.h"
#include "StudentController.h"


UserPageJsonVO::Wrapper UserController::executeQueryAll(const UserQuery::Wrapper& query)
{
	UserService us;
	auto vo = UserPageJsonVO::createShared();
	vo->success(us.listAll(query));
	return vo;
}









