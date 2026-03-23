#pragma once
#ifndef _APPOINTMENTCONTROLLER_H_
#define _APPOINTMENTCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/schedule/AppointmentVO.h"
#include "domain/dto/schedule/AppointmentDTO.h"
#include "domain/query/schedule/AppointmentQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class AppointmentController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(AppointmentController);
public:		
	// 3.1 定义查询接口描述
	ENDPOINT_INFO(appointment) {
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("schedule.appointment.info"));
		// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(NoDataJsonVO);
		// 定义标签
		API_DEF_ADD_TAG("schedule");
		// 定义其他查询参数描述
		API_DEF_ADD_QUERY_PARAMS(String, "courseId", ZH_WORDS_GETTER("schedule.appointment.courseId"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "studentId", ZH_WORDS_GETTER("student.id"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "date", ZH_WORDS_GETTER("schedule.appointment.date"), "", true);

	}

	// 定义接口
	ENDPOINT("GET", "/c5/schedule/appointment", appointment, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(query, AppointmentQuery, queryParams);
		// 呼叫执行函数响应结果
		return createDtoResponse(Status::CODE_200, executeAppointment(query));
	}

private:
	NoDataJsonVO::Wrapper executeAppointment(const AppointmentQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif