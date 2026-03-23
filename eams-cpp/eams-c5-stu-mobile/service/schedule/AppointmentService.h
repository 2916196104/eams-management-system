#pragma once
#ifndef _APPOINTMENTSERVICE_H_
#define _APPOINTMENTSERVICE_H_

#include "dao/schedule/AppointmentDAO.h"
#include "domain/query/schedule/AppointmentQuery.h"
#include "domain/vo/schedule/AppointmentVO.h"

class AppointmentService
{
public:
	AppointmentDTO::Wrapper insert(const AppointmentQuery::Wrapper& query);
};

#endif // !_APPOINTMENTSERVICE_H_