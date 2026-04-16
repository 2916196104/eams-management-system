#pragma once
#ifndef _COURSECONTROLLER_H_
#define _COURSECONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/Course/CourseVO.h"
#include "domain/query/Course/CourseQuery.h"
#include "domain/dto/Course/CourseDTO.h"
#include "ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG  ZH_WORDS_GETTER("course.field.course")

class CourseController : public web::server::api::ApiController
{
	API_ACCESS_DECLARE(CourseController);
public:
	// 1. 根据课程Id查询课程详情
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("course.detail.summary"), queryCourseDetail, CourseDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "courseId", ZH_WORDS_GETTER("course.field.courseId"), "", true);
	);

	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c7-workbench/courseDetail", queryCourseDetail,
		QUERIES(QueryParams, queryParams),
		execQueryCourseDetail(queryParams)
	);

	// 2. 分页查询课程列表
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("course.list.summary"), queryPage, CourseQuery, CoursePageJsonVO::Wrapper, API_TAG)
		API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7-workbench/courseList", queryPage, QUERIES(QueryParams, queryParams),
			API_HANDLER_QUERY_PARAM(query, CourseQuery, queryParams);
	API_HANDLER_RESP_VO(execQueryPage(query));
		);

private:
	// 分页查询
	CoursePageJsonVO::Wrapper execQueryPage(const CourseQuery::Wrapper& query);
	// 根据课程名字查询课程详情
	CourseDetailJsonVO::Wrapper execQueryCourseDetail(const QueryParams& queryParams);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#endif