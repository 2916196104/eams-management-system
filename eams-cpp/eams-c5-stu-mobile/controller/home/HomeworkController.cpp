#include "stdafx.h"
#include"HomeworkController.h"

StringJsonVO::Wrapper HomeworkController::executeQueryHomework(const PageQuery::Wrapper& query) {
	//创建一个响应结果
	auto vo = StringJsonVO::createShared();
	vo->success(ZH_WORDS_GETTER("homework.resp"));
	return vo;
}