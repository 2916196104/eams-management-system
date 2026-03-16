#pragma once
#ifndef _INTENDEDSTUDENT_CONTROLLER_
#define _INTENDEDSTUDENT_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/intendedstudent/IntendedStudentQuery.h"
#include "domain/dto/intendedstudent/IntendedStudentDTO.h"
#include "domain/vo/intendedstudent/IntendedStudentVO.h"

// 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("sample.tags.t1")

/**
 *	意向成员控制器
 */
class IntendedStudentController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(IntendedStudentController);

public:
	// 导出接口（无分页，无锁）
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("sample.export.summary"), exportSample, Void, API_TAG);
	API_HANDLER_ENDPOINT_NOPARAM(API_M_GET, "/sample/export", exportSample, execExportSample());

	// 导入接口（无锁）
	API_DEF_ENDPOINT_INFO_FILE(ZH_WORDS_GETTER("sample.import.summary"), importSample, SampleImportDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT(API_M_POST, "/sample/import", importSample, REQUEST(std::shared_ptr<IncomingRequest>, request), execImportSample(request));

private:
	std::shared_ptr<OutgoingResponse> execExportSample();
	StringJsonVO::Wrapper execImportSample(std::shared_ptr<IncomingRequest> request);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController) 
#endif // _INTENDEDSTUDENT_CONTROLLER_