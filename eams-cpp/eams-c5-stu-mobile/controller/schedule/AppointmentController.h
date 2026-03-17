#pragma once
#ifndef _APPOINTMENTCONTROLLER_H_
#define _APPOINTMENTCONTROLLER_H_

#include <oatpp-swagger/Controller.hpp>
#include "ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(ApiController);

class AppointmentController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(AppointmentController);
public:		//定义接口
	/*ENDPOINT_INFO(getAppointments) {
		API_DEF_ENDPOINT_INFO_AUTH("getAppointments", getAppointments, JsonVO::Wrapper, API_HANDLER_PAGE_PARAME);
	}
	ENDPOINT("GET", "/appointments", getAppointments, API_HANDLER_PAGE_PARAME, API_HANDLER_AUTH_PARAME) {

	}*/

};

#include OATPP_CODEGEN_END(ApiController)

#endif