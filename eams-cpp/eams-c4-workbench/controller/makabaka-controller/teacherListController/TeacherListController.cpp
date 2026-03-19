#include"stdafx.h"
#include"TeacherListController.h"

TeacherPageJsonVO::Wrapper TeacherListController::executeGetTeacherList(const TeacherQuery::Wrapper& query) {
	auto vo = TeacherPageJsonVO::createShared();
	auto pageDto = TeacherPageDTO::createShared();
	vo->success(pageDto);
	return vo;
}