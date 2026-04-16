#pragma once




#ifndef _ENROLLCOURSESCONTROLLER_H_
#define _ENROLLCOURSESCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/query/home/EnrollCourse/EnrollCourseQuery.h"
#include "domain/dto/home/EnrollCourse/EnrollCourseDTO.h"
#include "domain/vo/home/EnrollCourse/EnrollCourseVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class EnrollCourseController: public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(EnrollCourseController);
public:
	ENDPOINT_INFO(EnrollCourse) {
		info->summary = ZH_WORDS_GETTER("EnrollCourse.query-all.summary");
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON(EnrollCoursePageJsonVO::Wrapper);
		API_DEF_ADD_RSP_JSON_WRAPPER(EnrollCoursePageJsonVO);
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_TAG(ZH_WORDS_GETTER("EnrollCourse.tag"));
		info->queryParams.add<Int32>("student_id").description = ZH_WORDS_GETTER("EnrollCourse.field.student_id");
		info->queryParams["student_id"].addExample("default", oatpp::Int32(1));


	}
	ENDPOINT(API_M_GET, "c5home/enrollcourse", EnrollCourse, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, EnrollCourseQuery, params);
		API_HANDLER_RESP_VO(executeQueryEnrollCourse(query));
	}
private:
	EnrollCoursePageJsonVO::Wrapper executeQueryEnrollCourse(const EnrollCourseQuery::Wrapper& query);
};


#include OATPP_CODEGEN_END(ApiController)

#endif