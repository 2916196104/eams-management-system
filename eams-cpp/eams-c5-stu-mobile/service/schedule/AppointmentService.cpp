#include "stdafx.h"
#include "AppointmentService.h"
#include "domain/dto/schedule/AppointmentDTO.h"

std::string AppointmentService::insert(const AppointmentAddDTO::Wrapper& dto)
{
	AppointmentDAO dao;
	std::string msg = dao.insertAppointment(dto);
	return msg;
}