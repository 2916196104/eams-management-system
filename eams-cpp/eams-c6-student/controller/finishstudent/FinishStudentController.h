#pragma once
#ifndef _FINISH_STUDENT_CONTROLLER_H_
#define _FINISH_STUDENT_CONTROLLER_H_

#include "ApiHelper.h"
#include "Macros.h"
#include "ServerInfo.h"
#include "domain/query/finishstudent/FinishStudentQuery.h"
#include "domain/vo/finishstudent/FinishStudentVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
using namespace oatpp;
#define API_TAG ZH_WORDS_GETTER("finishstudent.api-tag")
/**
 * 结业学员控制器
 */
class FinishStudentController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(FinishStudentController);
private:
	//FinishStudentService m_finishStudentService;
public:
	// 导出接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("finishstudent.interface.export-finish-student"), exportFinishStudent, FinishStudentQuery, oatpp::Void, API_TAG);
	// 导出接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c6/finish-student/export", exportFinishStudent, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, FinishStudentQuery, queryParams); return execExportFinishStudent(query););

	// 导入接口描述
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("finishstudent.interface.import-finish-student"), importFinishStudent, oatpp::swagger::Binary, FinishStudentImportResultJsonVO::Wrapper, API_TAG);
	// 导入接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c6/finish-student/import", importFinishStudent, REQUEST(std::shared_ptr<IncomingRequest>, request), execImportFinishStudent(request));

private:
	std::shared_ptr<OutgoingResponse> execExportFinishStudent(const FinishStudentQuery::Wrapper& query);
	FinishStudentImportResultJsonVO::Wrapper execImportFinishStudent(std::shared_ptr<IncomingRequest> request);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_FINISH_STUDENT_CONTROLLER_H_
