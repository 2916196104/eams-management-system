#pragma once
#ifndef _GETSTUDENTCOURSESCONTROLLER_H_
#define _GETSTUDENTCOURSESCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "domain/query/MyCustomers/MyCustomersQuery.h"
#include "domain/vo/MyCustomers/MyCustomersVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("cus.tag")

class GetStudentCoursesController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(GetStudentCoursesController);
public:
	// 接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("cus.get-cus-courses.summary"),
		getStudentCourses,
		MyCustomersQuery,
		StudentCoursesPageJsonVO::Wrapper,
		API_TAG
	);

	// 接口路由
	API_HANDLER_ENDPOINT_AUTH(
		API_M_GET,
		"/MyCustomers/get-cus-courses/{name}",
		getStudentCourses,
		PATH(String, name),
		executeGetStudentCourses(name, authObject->getPayload())
	);

private:
	StudentCoursesPageJsonVO::Wrapper executeGetStudentCourses(const String& name, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // _GETSTUDENTCOURSESCONTROLLER_H_