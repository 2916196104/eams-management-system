#pragma once
#ifndef COURSERECORDCONTROLLER_H
#define COURSERECORDCONTROLLER_H

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/CourseRecord/CourseRecordVO.h"
#include "domain/query/CourseRecord/CourseRecordQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("CourseRecord.tag")

/**
 * 上课记录控制器
 */
class CourseRecordController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(CourseRecordController);
public:
	// 查询上课记录接口描述
	ENDPOINT_INFO(queryCourseRecord) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("CourseRecord.summary"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_RSP_JSON_WRAPPER(CourseRecordPageJsonVO);
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(UInt64, "student_id", ZH_WORDS_GETTER("CourseRecord.field.student_id"), 1, false);
		API_DEF_ADD_QUERY_PARAMS(UInt64, "course_id", ZH_WORDS_GETTER("CourseRecord.field.course_id"), 1, false);
	}
	// 查询上课记录接口处理
	ENDPOINT(API_M_GET, "/course-record", queryCourseRecord, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, CourseRecordQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryCourseRecord(query));
	}

private:
	CourseRecordPageJsonVO::Wrapper execQueryCourseRecord(const CourseRecordQuery::Wrapper& query);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif // !COURSERECORDCONTROLLER_H
