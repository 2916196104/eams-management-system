#include "stdafx.h"
#include "AppointmentController.h"
#include "service/schedule/AppointmentService.h"

NoDataJsonVO::Wrapper AppointmentController::executeAppointment(const AppointmentQuery::Wrapper& query)
{
	NoDataJsonVO::Wrapper jvo = NoDataJsonVO::createShared();
	ResultStatus res = AppointmentService().insert(query);
	
	jvo->init(res);
	return jvo;
}