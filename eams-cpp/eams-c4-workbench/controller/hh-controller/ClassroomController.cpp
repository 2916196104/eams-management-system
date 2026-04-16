#include "ClassroomController.h"
#include "../../service/workbench/hh-service/HhService.h"

ClassroomPageJsonVO::Wrapper ClassroomController::execQueryClassroom(const ClassroomQuery::Wrapper& query) {
	// 构建返回对象
	auto jvo = ClassroomPageJsonVO::createShared();

	// 查询
	auto res = HhService().listAllClassroom(query);
	jvo->success(res);
	return jvo;
}