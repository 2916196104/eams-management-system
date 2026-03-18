#pragma once


#ifndef __RECORD_NAME_H__
#define __RECORD_NAME_H__
#include "domain/GlobalInclude.h"
#include "domain/query/timetable/GetDetailCSQuery.h"
#include "domain/query/timetable/GetStuListQuery.h"
#include "domain/vo/timetable/GetDetailCSVO.h"
#include "domain/vo/timetable/GetStuListVO.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)


class Record_name: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(Record_name);
public:		//定义接口
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("api.get-detail-cs.title"),
		getDetailCS,
		GetDetailCSJsonVO::Wrapper,
		"GetDetailCS",
		API_DEF_ADD_QUERY_PARAMS(UInt64, "lesson_id", ZH_WORDS_GETTER("api.get-detail-cs.param.lesson-id"), 10002, true);
	);

	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,
		"/timetable/get-detail-cs",
		getDetailCS,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, GetDetailCSQuery, queryParams);
		auto vo = execGetDetailCS(query);
		API_HANDLER_RESP_VO(vo);
	);

	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("api.get-cs-stu-list.title"),
		getStuList,
		GetStuListJsonVO::Wrapper,
		"GetCSStuList",
		API_DEF_ADD_QUERY_PARAMS(UInt64, "page_index", ZH_WORDS_GETTER("api.get-cs-stu-list.param.page-index"), 1, false);
		API_DEF_ADD_QUERY_PARAMS(UInt64, "page_size", ZH_WORDS_GETTER("api.get-cs-stu-list.param.page-size"), 10, false);
	);

	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,
		"/timetable/get-stu-list",
		getStuList,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, GetStuListQuery, queryParams);
		auto vo = execGetStuList(query);
		API_HANDLER_RESP_VO(vo);
	);

private:	//定义接口执行函数
	GetDetailCSJsonVO::Wrapper execGetDetailCS(const GetDetailCSQuery::Wrapper& query);
	GetStuListJsonVO::Wrapper execGetStuList(const GetStuListQuery::Wrapper& query);

};

#include OATPP_CODEGEN_END(ApiController)

#endif