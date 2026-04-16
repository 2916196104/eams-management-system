#include "stdafx.h"
#include "RegisterController.h"
#include "../../service/Course/RegisterService.h"

StringJsonVO::Wrapper RegisterController::execSave(const RegisterAddDTO::Wrapper& dto, const PayloadDTO& payload)
{
	dto->setPayload(&payload);
	RegisterService serv;
	auto resultId = serv.saveReg(dto);

	auto vo = StringJsonVO::createShared();
	if (resultId.empty()) {
		vo->data = "Save failed";
		vo->code = 1;
	}
	else {
		vo->data = resultId;
		vo->code = 0;
	}
	return vo;
}