#include "stdafx.h"
#include "ClassroomController.h"
#include "service/Schedule/ClassroomService.h"

ClassroomPageJsonVO::Wrapper ClassroomController::execQueryPage(const ClassroomQuery::Wrapper& query)
{
	ClassroomService us;
	auto vo = ClassroomPageJsonVO::createShared();
	vo->success(us.listAll(query));
	return vo;
}