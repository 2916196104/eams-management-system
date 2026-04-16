#pragma once
#ifndef _APPOINTMENTDAO_H_
#define _APPOINTMENTDAO_H_

#include "BaseDAO.h"
#include "domain/query/schedule/AppointmentQuery.h"
#include "domain/do/schedule/AppointmentDO.h"
#include "domain/dto/schedule/AppointmentDTO.h"

class AppointmentDAO : public BaseDAO
{
private:
	// 利用雪花算法生成唯一ID
	std::string generateSnowFlakeId();
	// 获取试听课次id
	std::string getLessonId(const AppointmentAddDTO::Wrapper& dto);
	// 获取顾问id
	std::string getCounselorId(const AppointmentAddDTO::Wrapper& dto);
	// 获取当前时间
	/*std::string getCurrentDateTime();*/
public:
	std::string insertAppointment(const AppointmentAddDTO::Wrapper& dto);
};

#endif // !_APPOINTMENTDAO_H_
