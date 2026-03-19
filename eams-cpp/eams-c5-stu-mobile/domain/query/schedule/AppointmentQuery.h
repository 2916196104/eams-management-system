#pragma once
#ifndef _APPOINTMENTVO_H_
#define _APPOINTMENTVO_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class AppointmentQuery : public PageQuery
{
	DTO_INIT(AppointmentQuery, PageQuery);

	// Ô¤Ô¼id
	DTO_FIELD(String, appointmentId); 
	DTO_FIELD_INFO(appointmentId) {
		info->description = ZH_WORDS_GETTER("c5.schedule.appointment.id");
	}

	// Ñ§Éúid
	DTO_FIELD(String, studentId);
	DTO_FIELD_INFO(studentId) {
		info->description = ZH_WORDS_GETTER("c5.student.id");
	};
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_APPOINTMENTVO_H_