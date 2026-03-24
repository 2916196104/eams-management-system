#pragma once
#ifndef _APPOINTMENTDAO_H_
#define _APPOINTMENTDAO_H_

#include "BaseDAO.h"
#include "domain/query/schedule/AppointmentQuery.h"
#include "domain/do/schedule/AppointmentDO.h"

class AppointmentDAO : public BaseDAO
{
private:
	// 利用雪花算法生成唯一ID
	std::string generateSnowFlakeId();
	// 获取试听课次id
	std::string getLessonId(const AppointmentQuery::Wrapper& query);
	// 获取顾问id
	std::string getCounselorId(const AppointmentQuery::Wrapper& query);
	// 获取当前时间
	std::string getCurrentDateTime();
public:
	std::string insertAppointment(const AppointmentQuery::Wrapper& query);
};

#endif // !_APPOINTMENTDAO_H_
