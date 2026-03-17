#pragma once


#ifndef __RECORD_NAME_H__
#define __RECORD_NAME_H__
#include "domain/GlobalInclude.h"
#include "domain/query/timetable/GetDetailCSQuery.h"
#include "domain/query/timetable/GetStuListQuery.h"
#include "domain/vo/timetable/GetDetailCSVO.h"
#include "domain/vo/timetable/GetStuListVO.h"
#include "oatpp/web/server/api/ApiController.hpp"

#include "./domain/dto/timetable/TimetableDTO.h"
#include "./domain/vo/timetable/TimetableVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("set_status.flag")

class Record_name: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(Record_name);
public:		//定义接口
	API_DEF_ENDPOINT_INFO_AUTH(
		"Get lesson detail",
		getDetailCS,
		GetDetailCSJsonVO::Wrapper,
		"",
		API_DEF_ADD_QUERY_PARAMS(UInt64, "lesson_id", "Lesson ID", 10002, true);
	);

	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,
		"/timetable/record-name/get-detail-cs",
		getDetailCS,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, GetDetailCSQuery, queryParams);
		auto vo = execGetDetailCS(query);
		API_HANDLER_RESP_VO(vo);
	);

	API_DEF_ENDPOINT_INFO_AUTH(
		"Get student list with filters and pagination",
		getStuList,
		GetStuListJsonVO::Wrapper,
		"",
		API_DEF_ADD_QUERY_PARAMS(UInt64, "lesson_id", "Lesson ID", 10002, true);
		API_DEF_ADD_QUERY_PARAMS(String, "keyword", "Student keyword", "", false);
		API_DEF_ADD_QUERY_PARAMS(UInt64, "page_index", "Page index", 1, false);
		API_DEF_ADD_QUERY_PARAMS(UInt64, "page_size", "Page size", 10, false);
	);

	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,
		"/timetable/record-name/get-stu-list",
		getStuList,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, GetStuListQuery, queryParams);
		auto vo = execGetStuList(query);
		API_HANDLER_RESP_VO(vo);
	);
	// 1. 设置上课状态 接口的定义
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("set_status.title"), modifyStatus, SetStudyStatusRspJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/course-table/set-status", modifyStatus, BODY_DTO(SetStudyStatusDTO::Wrapper, dto), updateModifyStatus(dto, authObject->getPayload()));
private:	//定义接口执行函数
	GetDetailCSJsonVO::Wrapper execGetDetailCS(const GetDetailCSQuery::Wrapper& query);
	GetStuListJsonVO::Wrapper execGetStuList(const GetStuListQuery::Wrapper& query);

	SetStudyStatusRspJsonVO::Wrapper updateModifyStatus(const SetStudyStatusDTO::Wrapper& dto, const PayloadDTO& payload);
	
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif