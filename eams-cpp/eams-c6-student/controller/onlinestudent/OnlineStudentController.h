#pragma once
#ifndef _ONLINESTUDENT_CONTROLLER_
#define _ONLINESTUDENT_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/onlinestudent/OnlineStudentQuery.h"
#include "domain/dto/onlinestudent/OnlineStudentDTO.h"

// 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("onlinestudent.api-tag")

/**
 *	在线成员控制器
 */
class OnlineStudentController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(OnlineStudentController);

public:
	// 定义导出接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("onlinestudent.interface.export"),		// 标题
		exportExcel,											// 函数名
		Void,													// Swagger 无响应体
		API_TAG													// 标签
	);

	// 定义导出接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_POST,
		"/c6/student/online/export",
		exportExcel,
		BODY_DTO(List<String>, ids),
		auto response = execExportExcel(ids);
		return response;
	);

	// 定义导入接口描述
	API_DEF_ENDPOINT_INFO_FILE_AUTH(
		ZH_WORDS_GETTER("onlinestudent.interface.import"),		// 标题
		importExcel,											// 函数名
		OnlineImportDTO::Wrapper,								// 文件表单 DTO
		StringJsonVO::Wrapper,									// 响应 JSON
		API_TAG													// 标签
	);
	// 定义导入接口处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,												// POST 方法
		"/c6/student/online/import",							// URL
		importExcel,											// 函数名
		REQUEST(std::shared_ptr<IncomingRequest>, request),		// 接收文件
		execImportExcel(request, authObject->getPayload())		// 执行导入
	);

	// 定义修改顾问接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("onlinestudent.interface.modify-counselor"),	// 标题
		modifyCounselor,												// 函数名
		StringJsonVO::Wrapper,											// Swagger 响应体
		API_TAG															// 标签
	);
	// 定义修改顾问接口处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_PUT,														// PUT 方法
		"/c6/student/online/counselor/modify",							// URL
		modifyCounselor,												// 函数名
		BODY_DTO(ModifyCounselorDTO::Wrapper, dto),						// 请求参数
		execModifyCounselor(dto)										// 执行修改
	);

private:
	// 执行导出
	std::shared_ptr<OutgoingResponse> execExportExcel(const List<String>& ids);
	// 执行导入
	StringJsonVO::Wrapper execImportExcel(std::shared_ptr<IncomingRequest> request, const PayloadDTO& payload);
	// 执行修改顾问
	StringJsonVO::Wrapper execModifyCounselor(const ModifyCounselorDTO::Wrapper& dto);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController) 
#endif // _INTENDEDSTUDENT_CONTROLLER_