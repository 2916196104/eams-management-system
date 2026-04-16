#pragma once
#ifndef _SUMMARYCLASSCONTROLLER_H_
#define _SUMMARYCLASSCONTROLLER_H_

#include "../../domain/GlobalInclude.h"
#include "../../domain/vo/summaryclass/SummaryClassVO.h"

#include "../../domain/query/summaryclass/SummaryClassQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class SummaryClassController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(SummaryClassController);

public:
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("summaryclass.interface.query-summaryclass"),
		summaryclassquery,
		SummaryClassPageJsonVO::Wrapper,
		ZH_WORDS_GETTER("summaryclass.api-tag"),
		API_DEF_ADD_QUERY_PARAMS(String, "studentName", ZH_WORDS_GETTER("summaryclass.field.student.student-name"), "zhang san", false);
		API_DEF_ADD_QUERY_PARAMS(String, "courseName", ZH_WORDS_GETTER("summaryclass.field.student.course-name"), "math", false);
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