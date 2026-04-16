#pragma once

#ifndef _CUSTOMER_CONTROLLER_
#define _CUSTOMER_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/hh-dto/CustomerDTO.h"
#include "domain/query/hh-query/CustomerQuery.h"
#include "domain/vo/hh-vo/CustomerVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController) // 开始代码生成

#define API_TAG ZH_WORDS_GETTER("customer.tags.t1")

class CustomerController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(CustomerController);
public:
	// 1.客户分页查询接口
		// 前端传递page信息，然后page信息被解析，之后再被解析为CustomerQuery，无需额外添加其他查询参数
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("customer.get.summary"), queryCustomer, CustomerQuery, CustomerPageJsonVO::Wrapper, API_TAG
	);
	// 1.客户分页查询接口处理
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/c4-workbench/customer", queryCustomer, CustomerQuery,
		execQueryCustomer(query, authObject->getPayload()));
	// 2.客户详情查询接口（通过ID查询）
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("customer.detail.summary"), queryDetailById, CustomerDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("customer.field.id"), "123", true);
	);
	// 2.客户详情查询接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c4-workbench/customer/detail", queryDetailById, QUERY(String, id), execQueryDetailById(id));
	// 3.客户课程查询接口（通过ID查询）
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("customer.lesson.summary"), queryLessonById, CustomerLessonListJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("customer.field.id"), "123", true);
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c4-workbench/customer/lesson", queryLessonById, QUERY(String, id), execQueryLessonById(id));
private:
	CustomerPageJsonVO::Wrapper execQueryCustomer(const CustomerQuery::Wrapper& query, const PayloadDTO& payload);
	CustomerDetailJsonVO::Wrapper execQueryDetailById(const String& id);
	CustomerLessonListJsonVO::Wrapper execQueryLessonById(const String& id);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) // 结束代码生成

#endif