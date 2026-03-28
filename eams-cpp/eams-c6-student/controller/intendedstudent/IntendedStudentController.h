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
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("intendedstudent.interface.export"),	    // 标题
		exportExcel,												// 函数名
		Void,														// Swagger 无响应体
		API_TAG														// 标签
	);
	// 定义导出接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_POST,
		"/c6/student/intended/export",
		exportExcel,
		BODY_DTO(List<String>, ids),
		auto response = execExportExcel(ids);
	return response;
		);

	// 定义导入接口描述
	API_DEF_ENDPOINT_INFO_FILE_AUTH(
		ZH_WORDS_GETTER("intendedstudent.interface.import"),		// 标题
		importExcel,												// 函数名
		IntendedImportDTO::Wrapper,									// 文件表单DTO
		StringJsonVO::Wrapper,										// 响应JSON
		API_TAG														// 标签
	);
	// 定义导入接口处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,													// POST方法
		"/c6/student/intended/import",								// URL
		importExcel,												// 函数名
		REQUEST(std::shared_ptr<IncomingRequest>, request),			// 接收文件
		execImportExcel(request, authObject->getPayload())			// 执行导入
	);

private:
	// 执行导出
	std::shared_ptr<OutgoingResponse> execExportExcel(const List<String>& ids);
	// 执行导入
	StringJsonVO::Wrapper execImportExcel(std::shared_ptr<IncomingRequest> request, const PayloadDTO& payload);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController) 
#endif // _INTENDEDSTUDENT_CONTROLLER_