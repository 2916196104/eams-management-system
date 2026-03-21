#include"stdafx.h"
#include"GetRegistRecordListController.h"

StringJsonVO::Wrapper GetRegistRecordListController::executeQueryRegistRecordList(const PageQuery::Wrapper& query) {
	auto vo = StringJsonVO::createShared();
	vo->success(ZH_WORDS_GETTER("translation.resp"));
	return vo;
}