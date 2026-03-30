#pragma once
#ifndef _APPOINTMENTDTO_
#define _APPOINTMENTDTO_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class AppointmentAddDTO : public oatpp::DTO
{
	DTO_INIT(AppointmentAddDTO, DTO);

	// 预约时间
	DTO_FIELD(String, date);
	DTO_FIELD_INFO(date) {
		info->description = ZH_WORDS_GETTER("schedule.appointment.date");
	};

	// 学生id
	DTO_FIELD(String, studentId);
	DTO_FIELD_INFO(studentId) {
		info->description = ZH_WORDS_GETTER("student.id");
	};

	// 课程id
	DTO_FIELD(String, courseId);
	DTO_FIELD_INFO(courseId) {
		info->description = ZH_WORDS_GETTER("schedule.appointment.courseId");
	};

	// 关联一个PayloadDTO负载数据对象
protected: const PayloadDTO* _payload; public: const PayloadDTO* getPayload(void) const {
	return _payload;
}public: void setPayload(const PayloadDTO* var) {
	_payload = var;
};
};

class AppointmentDTO : public AppointmentAddDTO
{
	DTO_INIT(AppointmentDTO, AppointmentAddDTO);

	// 预约id
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("schedule.appointment.id");
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


	// 试听课次id
	DTO_FIELD(String, lessonId);
	DTO_FIELD_INFO(lessonId) {
		info->description = ZH_WORDS_GETTER("schedule.appointment.lessonId");
	};
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_APPOINTMENTDTO_
