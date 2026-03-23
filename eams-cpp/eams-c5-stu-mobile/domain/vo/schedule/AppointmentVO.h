#pragma once
#ifndef _APPOINTMENT_
#define _APPOINTMENT_

#include "../../GlobalInclude.h"
#include "domain/dto/schedule/AppointmentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class AppointmentJsonVO : public JsonVO<AppointmentDTO::Wrapper>
{
public:
	DTO_INIT(AppointmentJsonVO, JsonVO<AppointmentDTO::Wrapper>);
};

//class AppointmentPageJsonVO : JsonVO<AppointmentPageDTO::Wrapper>
//{
//public:
//	DTO_INIT(AppointmentPageJsonVO, JsonVO<AppointmentPageDTO::Wrapper>);
//};

#include OATPP_CODEGEN_END(DTO)

#endif // !APPOINTMENT_H
