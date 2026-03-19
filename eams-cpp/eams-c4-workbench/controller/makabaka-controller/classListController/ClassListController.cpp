#include"stdafx.h"
#include"ClassListController.h"

ClassPageJsonVO::Wrapper ClassListController::executeGetClassList(const ClassQuery::Wrapper& query) {
	auto vo = ClassPageJsonVO::createShared();
	auto page = ClassPageDTO::createShared();
	vo->success(page);
	return vo;
}