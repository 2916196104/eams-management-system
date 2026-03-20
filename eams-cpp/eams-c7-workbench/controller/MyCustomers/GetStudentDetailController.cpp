#include "stdafx.h"
#include "GetStudentDetailController.h"

MyCustomersJsonVO::Wrapper GetStudentDetailController::executeGetMyCustomersDetails(const String& name, const PayloadDTO& payload)
{
	auto vo = MyCustomersJsonVO::createShared();
	return vo;
}