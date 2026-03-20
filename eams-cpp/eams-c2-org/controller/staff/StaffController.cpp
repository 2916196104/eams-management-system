#include "stdafx.h"
#include "StaffController.h"

StringJsonVO::Wrapper StaffController::executeStaffPassWordChange(const StaffChangePasswordDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();
	//serviceÊµÏÖÐÞ¸ÄÃÜÂë
	jvo->success("");
	return jvo;
}

StringJsonVO::Wrapper StaffController::executeStaffListExport(const StaffExportQueryDto::Wrapper& exportQuery)
{
	auto jvo = StringJsonVO::createShared();
	jvo->success("");
	return jvo;
}
