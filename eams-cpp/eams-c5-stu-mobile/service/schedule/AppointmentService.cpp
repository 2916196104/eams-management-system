#include "stdafx.h"
#include "AppointmentService.h"
#include "domain/dto/schedule/AppointmentDTO.h"

AppointmentDTO::Wrapper AppointmentService::insert(const AppointmentQuery::Wrapper& query)
{
	AppointmentDAO dao;
	AppointmentDTO::Wrapper dto = AppointmentDTO::createShared();
	PtrAppointmentDO ptrdo = dao.insertAppointment(query);
	auto &appoinmtentDO = *ptrdo;
	ZO_STAR_DOMAIN_DO_TO_DTO(dto, appoinmtentDO, id, Id, courseId, CourseId, lessonId, LessonId,
		studentId, StudentId, addTime, AddTime, counselorId, CounselorId);
	return dto;
}