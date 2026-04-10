#pragma once
#ifndef _APPOINTMENTCONTROLLER_H_
#define _APPOINTMENTCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/dto/schedule/AppointmentDTO.h"
#include "domain/query/schedule/AppointmentQuery.h"
#include "domain/vo/BaseJsonVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class AppointmentController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(AppointmentController);
public:		
	
	// 3.1 定义新增接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("schedule.appointment.info"), appointment, StringJsonVO::Wrapper, ZH_WORDS_GETTER("schedule.summary"));
	// 3.2 定义新增接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c5schedule/appointment", appointment, BODY_DTO(AppointmentAddDTO::Wrapper, dto), executeAppointment(dto, authObject->getPayload()));


private:
	StringJsonVO::Wrapper executeAppointment(const AppointmentAddDTO::Wrapper& dto, const PayloadDTO& payload);
};

#include OATPP_CODEGEN_END(ApiController)

#endif