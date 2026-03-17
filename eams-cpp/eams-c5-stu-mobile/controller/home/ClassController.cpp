#include "stdafx.h"
#include "ClassController.h"

StringJsonVO::Wrapper ClassController::executeQueryClass(const PageQuery::Wrapper& query) {
	auto vo=StringJsonVO::createShared();
	vo->success("success");
	return vo;
}