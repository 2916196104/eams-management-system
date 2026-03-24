#include "stdafx.h"
#include "RegisterController.h"
#include "service/login/RegisterService.h"

NoDataJsonVO::Wrapper RegisterController::executeRegister(const RegisterQuery::Wrapper& query)
{
	NoDataJsonVO::Wrapper jvo = NoDataJsonVO::createShared();
	
	std::string msg = RegisterService().validate(query);
	if (msg == "success")
	{
		RegisterService().insert(query);
		ResultStatus status(msg, 200);
		jvo->init(status);
	}
	else
	{
		ResultStatus status(msg, 400);
		jvo->init(status);
	}

	return jvo;
}