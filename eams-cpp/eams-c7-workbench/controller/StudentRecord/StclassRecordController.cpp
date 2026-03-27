
#include "stdafx.h"
#include "StclassRecordController.h"
#include "../../service/StudentRecord/stclassrecord/StclassRecordService.h"
#include "../ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "PdfComponent.h"

StclassRecordPageJsonVO::Wrapper StclassRecordController::execQuerySample(const StlistQuery::Wrapper& query)
{
	// 查询数据
	auto result = StclassRecordService().listAll(query);
	// 响应结果
	auto jvo = StclassRecordPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}