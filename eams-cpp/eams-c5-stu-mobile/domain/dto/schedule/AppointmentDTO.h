#pragma once
#ifndef _APPOINTMENTDTO_
#define _APPOINTMENTDTO_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class AppointmentAddDTO : public oatpp::DTO
{
	DTO_INIT(AppointmentAddDTO, DTO);

	// 课程名称
	DTO_FIELD(String, courseId);
	DTO_FIELD_INFO(courseId) {
		info->description = ZH_WORDS_GETTER("schedule.appointment.courseId");
	};

	// 试听课次id
	DTO_FIELD(String, lessonId);
	DTO_FIELD_INFO(lessonId) {
		info->description = ZH_WORDS_GETTER("schedule.appointment.lessonId");
	};

	// 学生id
	DTO_FIELD(String, studentId);
	DTO_FIELD_INFO(studentId) {
		info->description = ZH_WORDS_GETTER("student.id");
	};

	// 预约时间
	DTO_FIELD(String, addTime);
	DTO_FIELD_INFO(addTime) {
		info->description = ZH_WORDS_GETTER("schedule.appointment.addTime");
	};

	// 顾问id
	DTO_FIELD(String, counselorId);
	DTO_FIELD_INFO(counselorId) {
		info->description = ZH_WORDS_GETTER("schedule.appointment.counselorId");
	}


	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

class AppointmentDTO : public AppointmentAddDTO
{
	DTO_INIT(AppointmentDTO, AppointmentAddDTO);

	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("schedule.appointment.id");
	};
};

//class AppointmentPageDTO : public PageDTO<AppointmentDTO::Wrapper>
//{
//	DTO_INIT(AppointmentPageDTO, PageDTO<AppointmentDTO::Wrapper>);
//};

#include OATPP_CODEGEN_END(DTO)

#endif // !_APPOINTMENTDTO_
