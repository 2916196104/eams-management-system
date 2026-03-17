#pragma once
#ifndef _ONLINESTUDENT_CONTROLLER_
#define _ONLINESTUDENT_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/onlinestudent/OnlineStudentQuery.h"

// 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("onlinestudent.api-tag")

/**
 *	意向成员控制器
 */
class OnlineStudentController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(OnlineStudentController);

public:
	// 定义导出接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("onlinestudent.interface.export"),										// 标题
		exportExcel,                                 // 函数名
		OnlineExcelQuery,                                 // 查询参数类型
		Void,                                        // Swagger 无响应体
		API_TAG                                      // 标签
	);
	// 定义导出接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,
		"/c6/student/online/export",
		exportExcel,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, OnlineExcelQuery, queryParams);
	return execExportExcel(query);
		);

private:
	// 执行导出
	std::shared_ptr<OutgoingResponse> execExportExcel(const OnlineExcelQuery::Wrapper& query);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController) 
#endif // _INTENDEDSTUDENT_CONTROLLER_