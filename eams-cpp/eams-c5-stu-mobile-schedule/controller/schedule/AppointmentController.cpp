#include "stdafx.h"
#include "AppointmentController.h"
#include "service/schedule/AppointmentService.h"

StringJsonVO::Wrapper AppointmentController::executeAppointment(const AppointmentAddDTO::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();

	dto->setPayload(&payload);
	std::string msg = AppointmentService().insert(dto);
	if (msg.front() >= '0' && msg.front() <= '9') jvo->success(msg);
	else jvo->fail(msg);
	
	return jvo;
}