
#include "stdafx.h"
#include "../../service/StudentRecord/stprofiledetails/StprofileDetailsService.h"
#include "StprofileDetailsController.h"

StprofileDetailsPageJsonVO::Wrapper StprofileDetailsController::execQuerySample(const StlistQuery::Wrapper& query)
{
	// 查询数据
	auto result = StprofileDetailsService().listAll(query);
	// 响应结果
	auto jvo = StprofileDetailsPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}