#include"stdafx.h"
#include"GetRegistRecordListController.h"

RegistRecordPageJsonVO::Wrapper GetRegistRecordListController::execQueryRegistRecordList(const RegistRecordQuery::Wrapper& query) {
	// 查询数据
	auto result = RegistRecordService().listAll(query);
	// 响应结果
	auto jvo = RegistRecordPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}