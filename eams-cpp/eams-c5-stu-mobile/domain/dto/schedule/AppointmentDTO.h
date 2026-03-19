#pragma once
#ifndef _APPOINTMENTDTO_
#define _APPOINTMENTDTO_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class AppointmentAddDTO : public oatpp::DTO
{
	DTO_INIT(AppointmentAddDTO, DTO);

	// 课程名称
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("c5.schedule.appointment.name");
	};

	// 教师
	DTO_FIELD(String, teacher);
	DTO_FIELD_INFO(teacher) {
		info->description = ZH_WORDS_GETTER("c5.schedule.appointment.teacher");
	};

	// 教室
	DTO_FIELD(String, classroom);
	DTO_FIELD_INFO(classroom) {
		info->description = ZH_WORDS_GETTER("c5.schedule.appointment.classroom");
	};

	// 开始时间
	DTO_FIELD(String, startTime);
	DTO_FIELD_INFO(startTime) {
		info->description = ZH_WORDS_GETTER("c5.schedule.appointment.startTime");
	};

	// 结束时间
	DTO_FIELD(String, endTime);
	DTO_FIELD_INFO(endTime) {
		info->description = ZH_WORDS_GETTER("c5.schedule.appointment.endTime");
	}

	// 班级(class是个关键字没法用)
	DTO_FIELD(String, team);
	DTO_FIELD_INFO(team) {
		info->description = ZH_WORDS_GETTER("c5.schedule.appointment.team");
	}

	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

class AppointmentDTO : public AppointmentAddDTO
{
	DTO_INIT(AppointmentDTO, AppointmentAddDTO);
	// 预约ID
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("schedule.appointment.id");
	};
};

class AppointmentPageDTO : public PageDTO<AppointmentDTO::Wrapper>
{
	DTO_INIT(AppointmentPageDTO, PageDTO<AppointmentDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_APPOINTMENTDTO_
