#pragma once
#ifndef _APPOINTMENTVO_H_
#define _APPOINTMENTVO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class AppointmentQuery : public oatpp::DTO
{
	DTO_INIT(AppointmentQuery, DTO);

	// 预约课程id
	DTO_FIELD(String, courseId);
	DTO_FIELD_INFO(courseId) {
		info->description = ZH_WORDS_GETTER("schedule.appointment.courseID");
	}

	// 预约日期
	DTO_FIELD(String, date);
	DTO_FIELD_INFO(date) {
		info->description = ZH_WORDS_GETTER("schedule.appointment.date");
	}

	// 学生id
	DTO_FIELD(String, studentId);
	DTO_FIELD_INFO(studentId) {
		info->description = ZH_WORDS_GETTER("student.id");
	};
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_APPOINTMENTVO_H_