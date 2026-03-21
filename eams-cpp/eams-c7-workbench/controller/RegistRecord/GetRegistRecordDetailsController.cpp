#include"stdafx.h"
#include"GetRegistRecordDetailsController.h"


StringJsonVO::Wrapper GetRegistRecordDetailsController::executeQueryRegistRecordDetails(const PageQuery::Wrapper& query) {
	auto vo = StringJsonVO::createShared();
	vo->success(ZH_WORDS_GETTER("translation.resp"));
	return vo;
}