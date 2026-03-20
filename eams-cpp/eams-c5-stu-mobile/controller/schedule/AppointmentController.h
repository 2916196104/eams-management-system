#pragma once
#ifndef _APPOINTMENTCONTROLLER_H_
#define _APPOINTMENTCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/schedule/AppointmentVO.h"
#include "domain/dto/schedule/AppointmentDTO.h"
#include "domain/query/schedule/AppointmentQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("c5.schedule.tag")


class AppointmentController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(AppointmentController);
public:		
	// 3.1 定义查询接口描述
	ENDPOINT_INFO(appointment) {
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("c5.schedule.appointment.info"));
		// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(AppointmentPageJsonVO);
		// 定义标签
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("c5.schedule.appointment.info"));
		// 定义分页查询参数描述
		API_DEF_ADD_PAGE_PARAMS();
		// 定义其他查询参数描述
		API_DEF_ADD_QUERY_PARAMS(String, "appointmentID", ZH_WORDS_GETTER("c5.schedule.appointment.id"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "studentID", ZH_WORDS_GETTER("c5.student.id"), "", true);
	}

	// 定义接口
	ENDPOINT("GET", "/c5/schedule/appointment", appointment, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(query, AppointmentQuery, queryParams);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(executeAppointment(query));
	}

private:
	AppointmentPageJsonVO::Wrapper executeAppointment(const AppointmentQuery::Wrapper& dto);
};

#include OATPP_CODEGEN_END(ApiController)

#endif