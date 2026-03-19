#include"stdafx.h"
#include"CheckInController.h"
StringJsonVO::Wrapper  CheckInController::executeCheckIn(const PageQuery::Wrapper& query) {
	//创建一个响应结果
	auto vo{ StringJsonVO::createShared() };
	vo->success(ZH_WORDS_GETTER("CheckIn.resp"));
	return vo;
}