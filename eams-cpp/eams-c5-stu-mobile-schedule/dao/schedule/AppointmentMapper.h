#pragma once
#ifndef _APPOINTMENTMAPPER_H_
#define _APPOINTMENTMAPPER_H_

#include "Mapper.h"
#include "domain/do/schedule/AppointmentDO.h"

class AppointmentMapper : public Mapper<AppointmentDO>
{
public:
	AppointmentDO mapper(ResultSet* resultSet) const override
	{
		AppointmentDO appointment;
		appointment.setId(resultSet->getString("id"));
		appointment.setLessonId(resultSet->getString("lesson_id"));
		appointment.setStudentId(resultSet->getString("student_id"));
		appointment.setAddTime(resultSet->getString("add_time"));
		appointment.setCourseId(resultSet->getString("course_id"));
		appointment.setCounselor(resultSet->getString("counselor"));
		return appointment;
	}
};

class PtrAppointmentMapper : public Mapper<PtrAppointmentDO>
{
public:
	PtrAppointmentDO mapper(ResultSet* resultSet) const override
	{
		PtrAppointmentDO appointment = std::make_shared<AppointmentDO>();
		appointment->setId(resultSet->getString("id"));
		appointment->setLessonId(resultSet->getString("lesson_id"));
		appointment->setStudentId(resultSet->getString("student_id"));
		appointment->setAddTime(resultSet->getString("add_time"));
		appointment->setCourseId(resultSet->getString("course_id"));
		appointment->setCounselor(resultSet->getString("counselor"));
		return appointment;
	}
};

#endif // !_APPOINTMENTMAPPER_H_