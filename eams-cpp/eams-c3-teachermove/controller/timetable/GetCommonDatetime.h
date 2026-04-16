#pragma once


#ifndef __GETCOMMONDATETIME_H__
#define __GETCOMMONDATETIME_H__
#include "domain/GlobalInclude.h"
#include "domain/query/timetable/GetCommonDatetimeQuery.h"
#include "domain/vo/timetable/CommonDatetimeVO.h"

#include "oatpp/web/server/api/ApiController.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("api.tag1")

class GetCommonDatetime : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(GetCommonDatetime);
public:		//定义接口
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("api.get-common-datetime.title"),
		getCommonDatetime,
		CommonDatetimeJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "date", ZH_WORDS_GETTER("api.get-common-datetime.param.date"), "2026-03-15", true);
	);

	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,
		"course/get-common-datetime",
		getCommonDatetime,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, GetCommonDatetimeQuery, queryParams);
		auto vo = execGetCommonDatetime(query);
		API_HANDLER_RESP_VO(vo);
	);

private:	//定义接口执行函数
	CommonDatetimeJsonVO::Wrapper execGetCommonDatetime(const GetCommonDatetimeQuery::Wrapper& query);

};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif