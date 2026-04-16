#pragma once


#ifndef __RECORD_NAME_H__
#define __RECORD_NAME_H__
#include "domain/GlobalInclude.h"
#include "domain/query/timetable/GetDetailCSQuery.h"
#include "domain/query/timetable/GetStuListQuery.h"
#include "domain/vo/timetable/GetDetailCSVO.h"
#include "domain/vo/timetable/GetStuListVO.h"
#include "domain/query/timetable/TimetableQuery.h"
#include "domain/dto//timetable/TimetableDTO.h"
#include "oatpp/web/server/api/ApiController.hpp"

#include "./domain/dto/timetable/TimetableDTO.h"
#include "./domain/vo/timetable/TimetableVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("api.tag")


class Record_name : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(Record_name);
public:		//定义接口
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("api.get-detail-cs.title"),
		getDetailCS,
		GetDetailCSJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_QUERY_PARAMS(UInt64, "lesson_id", ZH_WORDS_GETTER("api.get-detail-cs.param.lesson-id"), 10002, true);
	);

	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,
		"course/record-name/get-detail-cs",
		getDetailCS,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, GetDetailCSQuery, queryParams);
	auto vo = execGetDetailCS(query);
	API_HANDLER_RESP_VO(vo);
		);

	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("api.get-cs-stu-list.title"),
		getCSStuList,
		GetStuListJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_QUERY_PARAMS(UInt64, "page_index", ZH_WORDS_GETTER("api.get-cs-stu-list.param.page-index"), 1, false);
	API_DEF_ADD_QUERY_PARAMS(UInt64, "page_size", ZH_WORDS_GETTER("api.get-cs-stu-list.param.page-size"), 10, false);
		);

	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,
		"course/record-name/get-cs-stu-list",
		getCSStuList,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, GetStuListQuery, queryParams);
	auto vo = execGetStuList(query);
	API_HANDLER_RESP_VO(vo);
		);
	// 1. 设置上课状态 接口的定义
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("set_status.title"), modifyStatus, SetStudyStatusRspJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "course/record-name/set-status", modifyStatus, BODY_DTO(SetStudyStatusDTO::Wrapper, dto), updateModifyStatus(dto, authObject->getPayload()));

	// Define endpoints
	// Endpoint 1: Get student list (with conditions + pagination) - GetStuList

	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("timetable.endpoints.getStudentList.title"),
		GetStuList,
		StuListQuery,
		TimetableStudentPageJsonVO::Wrapper,
		API_TAG
	)

		API_HANDLER_ENDPOINT_QUERY_AUTH(
			API_M_GET, "course/record-name/stu-list", GetStuList, StuListQuery,
			execGetStuList(query, authObject->getPayload())
		)

		// Endpoint 2: Add student to lesson - InsertStuToCS

		API_DEF_ENDPOINT_INFO_AUTH(
			ZH_WORDS_GETTER("timetable.endpoints.insertStuToCS.title"),
			InsertStuToCS,
			StringJsonVO::Wrapper,
			API_TAG,
			API_DEF_NOTHING
		)

		API_HANDLER_ENDPOINT_AUTH(
			API_M_POST, "course/record-name/stu-add-to-cs", InsertStuToCS,
			BODY_DTO(AddStudentToLessonDTO::Wrapper, dto),
			execInsertStuToCS(dto, authObject->getPayload())
		)

		// Endpoint 3: Get student course list - GetStuClassList

		API_DEF_ENDPOINT_INFO_QUERY_AUTH(
			ZH_WORDS_GETTER("timetable.endpoints.getStudentCourseList.title"),
			GetStuClassList,
			StuClassQuery,
			ListJsonVO<TimetableStudentCourseDTO::Wrapper>::Wrapper,
			API_TAG
		)

		API_HANDLER_ENDPOINT_QUERY_AUTH(
			API_M_GET, "course/record-name/stu-course-list", GetStuClassList, StuClassQuery,
			execGetStuClassList(query, authObject->getPayload())
		)

private:
	GetDetailCSJsonVO::Wrapper execGetDetailCS(const GetDetailCSQuery::Wrapper& query);
	GetStuListJsonVO::Wrapper execGetStuList(const GetStuListQuery::Wrapper& query);
	SetStudyStatusRspJsonVO::Wrapper updateModifyStatus(const SetStudyStatusDTO::Wrapper& dto, const PayloadDTO& payload);
	// Declare execution functions

	TimetableStudentPageJsonVO::Wrapper execGetStuList(const StuListQuery::Wrapper& query, const PayloadDTO& payload);

	StringJsonVO::Wrapper execInsertStuToCS(const AddStudentToLessonDTO::Wrapper& dto, const PayloadDTO& payload);

	ListJsonVO<TimetableStudentCourseDTO::Wrapper>::Wrapper execGetStuClassList(const StuClassQuery::Wrapper& query, const PayloadDTO& payload);

};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#endif
