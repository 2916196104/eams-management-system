
#include "stdafx.h"
#include "HomeworkListController.h"
#include "service/Homework/homeworklist/HomeworkListService.h"
#include "../ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "PdfComponent.h"

HomeworkListPageJsonVO::Wrapper HomeworkListController::execQuerySample(const HomeworkListQuery::Wrapper& query)
{
	// 查询数据
	auto result = HomeworkListService().listAll(query);
	// 响应结果
	auto jvo = HomeworkListPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}