
#include "stdafx.h"
#include "StlistController.h"
#include "../../service/StudentRecord/stlist/StlistService.h"
#include "../ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "PdfComponent.h"

StlistPageJsonVO::Wrapper StlistController::execQuerySample(const StlistQuery::Wrapper& query)
{
	// 查询数据
	auto result = StlistService().listAll(query);
	// 响应结果
	auto jvo = StlistPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}
