#include "stdafx.h"
#include "controller/finishstudent/FinishStudentController.h"

std::shared_ptr<FinishStudentController::OutgoingResponse> FinishStudentController::execExportFinishStudent(const FinishStudentQuery::Wrapper& query)
{
	return nullptr;
}

FinishStudentImportResultJsonVO::Wrapper FinishStudentController::execImportFinishStudent(std::shared_ptr<IncomingRequest> request)
{
	return {};
}
