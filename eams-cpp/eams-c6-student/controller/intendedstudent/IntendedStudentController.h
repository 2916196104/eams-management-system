#pragma once
#ifndef _INTENDEDSTUDENT_CONTROLLER_
#define _INTENDEDSTUDENT_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/intendedstudent/IntendedStudentQuery.h"
#include "domain/dto/intendedstudent/IntendedStudentDTO.h"

// 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("intendedstudent.api-tag")

/**
 *	意向成员控制器
 */
class IntendedStudentController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(IntendedStudentController);

public:
	// 定义导出接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("intendedstudent.interface.export"),									// 标题
		exportExcel,                                 // 函数名
		IntendExcelQuery,                                 // 查询参数类型
		Void,                                        // Swagger 无响应体
		ZH_WORDS_GETTER("intendedstudent.api-tag")                                      // 标签
	);
	// 定义导出接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,
		"/c6/student/intended/export",
		exportExcel,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, IntendExcelQuery, queryParams);
		return execExportExcel(query);
	);

	// 定义导入接口描述
	API_DEF_ENDPOINT_INFO_FILE_AUTH(
		ZH_WORDS_GETTER("intendedstudent.interface.import"),									   // 标题
		importExcel,                                 // 函数名
		IntendImportDTO::Wrapper,                    // 文件表单DTO
		StringJsonVO::Wrapper,                       // 响应JSON
		API_TAG                                      // 标签
	);
	// 定义导出接口处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,                                  // POST方法
		"/c6/student/intended/import",               // URL
		importExcel,                                 // 函数名
		REQUEST(std::shared_ptr<IncomingRequest>, request),  // 接收文件
		execImportExcel(request, authObject->getPayload())   // 执行导入
	);

private:
	// 执行导出
	std::shared_ptr<OutgoingResponse> execExportExcel(const IntendExcelQuery::Wrapper& query);
	// 执行导入
	StringJsonVO::Wrapper execImportExcel(std::shared_ptr<IncomingRequest> request, const PayloadDTO& payload);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController) 
#endif // _INTENDEDSTUDENT_CONTROLLER_