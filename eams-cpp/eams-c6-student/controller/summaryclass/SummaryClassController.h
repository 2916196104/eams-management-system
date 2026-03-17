#pragma once
#ifndef _SUMMARYCLASSCONTROLLER_H_
#define _SUMMARYCLASSCONTROLLER_H_

#include "../../domain/GlobalInclude.h"
#include "../../domain/vo/summaryclass/SummaryClassVO.h"

#include "../../domain/query/summaryclass/SummaryClassQuery.h"

#define API_TAG ZH_WORDS_GETTER("SummaryClass.tag")

#include OATPP_CODEGEN_BEGIN(ApiController)

class SummaryClassController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(SummaryClassController);

public:
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("SummaryClass.summary"),
		summaryclassquery,
		SummaryClassPageJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "studentName", ZH_WORDS_GETTER("SummaryClass.field.studentName"), "zhang san", true);
		API_DEF_ADD_QUERY_PARAMS(String, "courseName", ZH_WORDS_GETTER("SummaryClass.field.courseName"), "math", true);
		API_DEF_ADD_PAGE_PARAMS();
	);

	API_HANDLER_ENDPOINT_QUERY_AUTH(
		API_M_GET,
		"c6/SummaryClass",
		summaryclassquery,
		SummaryClassQuery,
		excuteSummaryClassQuery(query)
	);
private:
	SummaryClassPageJsonVO::Wrapper excuteSummaryClassQuery(const SummaryClassQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif