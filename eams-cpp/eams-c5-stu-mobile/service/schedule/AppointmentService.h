#pragma once
#ifndef _APPOINTMENTSERVICE_H_
#define _APPOINTMENTSERVICE_H_

#include "dao/schedule/AppointmentDAO.h"
#include "domain/query/schedule/AppointmentQuery.h"

class AppointmentService
{
public:
	std::string insert(const AppointmentAddDTO::Wrapper& dto);
};

#endif // !_APPOINTMENTSERVICE_H_