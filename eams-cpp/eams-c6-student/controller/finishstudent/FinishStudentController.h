#pragma once
#ifndef _FINISH_STUDENT_CONTROLLER_H_
#define _FINISH_STUDENT_CONTROLLER_H_

#include "ApiHelper.h"
#include "Macros.h"
#include "ServerInfo.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/finishstudent/FinishStudentDTO.h"
#include "domain/query/finishstudent/FinishStudentQuery.h"
#include "domain/vo/finishstudent/FinishStudentVO.h"
#include "service/finishstudent/FinishStudentService.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
using namespace oatpp;
#define API_TAG ZH_WORDS_GETTER("finishstudent.api-tag")

class FinishStudentController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(FinishStudentController);
private:
	//FinishStudentService m_finishStudentService;
	FinishStudentService m_finishStudentService;
public:
	// export
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("finishstudent.interface.export-finish-student"), exportFinishStudent, Void, API_TAG);
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_POST, "/c6/finish-student/export", exportFinishStudent, BODY_DTO(List<UInt64>, ids),
		return execExportFinishStudent(ids););

	// import
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("finishstudent.interface.import-finish-student"), importFinishStudent, FinishStudentImportDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c6/finish-student/import", importFinishStudent, REQUEST(std::shared_ptr<IncomingRequest>, request), execImportFinishStudent(request));

private:
	std::shared_ptr<OutgoingResponse> execExportFinishStudent(const List<UInt64>& ids);
	StringJsonVO::Wrapper execImportFinishStudent(std::shared_ptr<IncomingRequest> request);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_FINISH_STUDENT_CONTROLLER_H_



