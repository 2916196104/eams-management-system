#pragma once
#ifndef _GETSTUDENTDETAILCONTROLLER_H_
#define _GETSTUDENTDETAILCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "domain/query/MyCustomers/MyCustomersQuery.h"
#include "domain/vo/MyCustomers/MyCustomersVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("cus.tag")

class GetStudentDetailController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(GetStudentDetailController);
public:
	// 接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("cus.get-cus-details.summary"),
		getStudentDetails,
		StudentDetailQuery,
		MyCustomerDetailJsonVO::Wrapper,
		API_TAG
	);

	// 接口路由
	API_HANDLER_ENDPOINT_AUTH(
		API_M_GET,
		"/c7-workbench/MyCustomers/get-cus-details/{id}",
		getStudentDetails,
		PATH(Int64, id),
		executeGetMyCustomersDetails(id, authObject->getPayload())
	);

private:
	MyCustomerDetailJsonVO::Wrapper executeGetMyCustomersDetails(const Int64& id, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // _GETSTUDENTDETAILCONTROLLER_H_