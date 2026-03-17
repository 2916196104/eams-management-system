#include "stdafx.h"
#include "ClassController.h"

StringJsonVO::Wrapper ClassController::executeQueryClassStudent(const PageQuery::Wrapper& query) {
	auto vo=StringJsonVO::createShared();
	vo->success(ZH_WORDS_GETTER("class.resp"));
	return vo;
}