#pragma once
#ifndef COURSEEVALUATECONTROLLER_H
#define COURSEEVALUATECONTROLLER_H

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/CourseEvaluate/CourseEvaluateVO.h"
//#include "domain/query/CourseEvaluate/CourseEvaluateQuery.h"
#include "domain/dto/CourseEvaluate/CourseEvaluateDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("CourseRecord.tag")

/**
 * 课程评价控制器
 */
class CourseEvaluateController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(CourseEvaluateController);
public:
	// 查询课程评价接口描述
	//ENDPOINT_INFO(queryCourseEvaluate) {
	//	API_DEF_ADD_TITLE(ZH_WORDS_GETTER("CourseEvaluate.get-summary"));
	//	API_DEF_ADD_AUTH();
	//	API_DEF_ADD_TAG(API_TAG);
	//	API_DEF_ADD_RSP_JSON_WRAPPER(CourseEvaluatePageJsonVO);
	//	API_DEF_ADD_PAGE_PARAMS();
	//	API_DEF_ADD_QUERY_PARAMS(UInt64, "student_id", ZH_WORDS_GETTER("CourseEvaluate.field.student_id"), 1, false);
	//	API_DEF_ADD_QUERY_PARAMS(UInt64, "course_id", ZH_WORDS_GETTER("CourseEvaluate.field.course_id"), 1, false);
	//}
	//// 查询课程评价接口处理
	//ENDPOINT(API_M_GET, "/c5/home/courseRecord/evaluate/list", queryCourseEvaluate, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
	//	API_HANDLER_QUERY_PARAM(query, CourseEvaluateQuery, queryParams);
	//	API_HANDLER_RESP_VO(execQueryCourseEvaluate(query));
	//}

	// 新增课程评价接口描述
	ENDPOINT_INFO(addCourseEvaluate) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("CourseEvaluate.post-summary"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);
	}
	// 新增课程评价接口处理
	ENDPOINT(API_M_POST, "/c5/home/courseRecord/evaluate", addCourseEvaluate, BODY_DTO(CourseEvaluateDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(execAddCourseEvaluate(dto, authObject->getPayload()));
	}

private:
	//CourseEvaluatePageJsonVO::Wrapper execQueryCourseEvaluate(const CourseEvaluateQuery::Wrapper& query);
	StringJsonVO::Wrapper execAddCourseEvaluate(const CourseEvaluateDTO::Wrapper& dto, const PayloadDTO& payload);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif // !COURSEEVALUATECONTROLLER_H
