#include "stdafx.h"
#include "AppointmentService.h"
#include "domain/dto/schedule/AppointmentDTO.h"

ResultStatus AppointmentService::insert(const AppointmentQuery::Wrapper& query)
{
	AppointmentDAO dao;
	std::string msg = dao.insertAppointment(query);
	if (msg == "success") return ResultStatus(msg, 200);
	else return ResultStatus(msg, 400);
}