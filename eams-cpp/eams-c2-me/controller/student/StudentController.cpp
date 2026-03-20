#include "stdafx.h"
#include "StudentController.h"


StudentPageJsonVO::Wrapper StudentController::executeQueryAll(const UserQuery::Wrapper& query)
{
	return StudentPageJsonVO::createShared();
}
