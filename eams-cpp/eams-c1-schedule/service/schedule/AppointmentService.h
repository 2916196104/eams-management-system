#pragma once
#ifndef _APPOINTMENT_SERVICE_H_
#define _APPOINTMENT_SERVICE_H_

#include "../../domain/dto/schedule/scheduleDTO.h" 

/**
 * 预约服务逻辑层
 */
class AppointmentService
{
public:
	// 提交预约申请（新增一条预约记录）
	// 这里返回 bool 表示是否预约成功
	bool addAppointment(const ScheduleAppointmentDTO::Wrapper& dto);
};

#endif // !_APPOINTMENT_SERVICE_H_