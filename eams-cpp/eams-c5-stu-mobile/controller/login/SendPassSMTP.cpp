#include "SendPassSMTP.h"
#include "stdafx.h"

StringJsonVO::Wrapper SendPassSMTPControl::executeSendSMTP(const PageQuery::Wrapper& query)
{
	//创建一个响应结果
	//指针
	auto vo = StringJsonVO::createShared();
	//传参
	vo->success(ZH_WORDS_GETTER("test.resp"));
	return vo;
}
