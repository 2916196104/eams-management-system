#include "stdafx.h"
#include "AppointmentController.h"
#include "service/schedule/AppointmentService.h"

AppointmentJsonVO::Wrapper AppointmentController::executeAppointment(const AppointmentQuery::Wrapper& query)
{
	AppointmentDTO::Wrapper dto = AppointmentService().insert(query);
	
	AppointmentJsonVO::Wrapper jvo = AppointmentJsonVO::createShared();
	jvo->success(dto);
	return jvo;
}