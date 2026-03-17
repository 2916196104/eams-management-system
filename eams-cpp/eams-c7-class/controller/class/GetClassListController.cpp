#include "stdafx.h"
#include "GetClassListController.h"
#include "../../domain/query/ClassQuery.h"
ClassPageJsonVO::Wrapper GetClassListController::executeGetClassList(const ClassQuery::Wrapper& query, const PayloadDTO& payload) {
	// 创建响应VO
	auto vo = ClassPageJsonVO::createShared();

	// 返回空数据
	auto pageDto = ClassPageDTO::createShared();
	vo->success(pageDto);

	return vo;
}