#include"stdafx.h"
#include"TeacherListController.h"
#include"../../../service/makabaka-service/TeacherListService.h"

TeacherPageJsonVO::Wrapper TeacherListController::executeGetTeacherList(const TeacherQuery::Wrapper& query) {
	//²éÑ¯Êı¾İ
	auto result = TeacherListService().listAll(query);
	auto vo = TeacherPageJsonVO::createShared();
	vo->success(result);
	return vo;
}