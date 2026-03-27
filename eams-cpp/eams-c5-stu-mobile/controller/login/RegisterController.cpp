#include "stdafx.h"
#include "RegisterController.h"
#include "service/login/RegisterService.h"

StringJsonVO::Wrapper RegisterController::executeRegister(const RegisterAddDTO::Wrapper& dto, const PayloadDTO& payload)
{
	StringJsonVO::Wrapper jvo = StringJsonVO::createShared();
	dto->setPayload(&payload);
	std::string msg = RegisterService().validate(dto);
	if (msg.front() >= '0' && msg.front() <= '9') jvo->success(msg);
	else jvo->fail(msg);

	return jvo;
}