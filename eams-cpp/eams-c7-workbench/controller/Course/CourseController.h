#pragma once
#ifndef _COURSECONTROLLER_H_
#define _COURSECONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/course/CourseVO.h"
#include "domain/query/course/CourseQuery.h"
#include "ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG "sample"

class CourseController : public web::server::api::ApiController
{
	API_ACCESS_DECLARE(CourseController);
public:
	// 1. 多条件查询课程详情
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("course.detail.summary"), queryCourseDetail, CourseListJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "coursename", ZH_WORDS_GETTER("course.field.courseName"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "startTime", ZH_WORDS_GETTER("course.field.startTime"), "2026-01-01", true);
		API_DEF_ADD_QUERY_PARAMS(String, "endTime", ZH_WORDS_GETTER("course.field.endTime"), "2026-01-01", true);
		API_DEF_ADD_QUERY_PARAMS(Int32, "courseNum", ZH_WORDS_GETTER("course.field.courseNum"), 0, true);
		API_DEF_ADD_QUERY_PARAMS(Int32, "coursePrice", ZH_WORDS_GETTER("course.field.coursePrice"), 0, true);
		API_DEF_ADD_QUERY_PARAMS(Int32, "actualPayment", ZH_WORDS_GETTER("course.field.actualPayment"), 0, true);
		API_DEF_ADD_QUERY_PARAMS(Int32, "discountPrice", ZH_WORDS_GETTER("course.field.discountPrice"), 0, true);
		API_DEF_ADD_QUERY_PARAMS(String, "tip", ZH_WORDS_GETTER("course.field.tip"), "", false);
		);
	// 
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c7/workbench/courseDetail", queryCourseDetail,
		QUERIES(QueryParams, queryParams),
		execQueryCourseDetail(queryParams)
	);
	// 3.1 定义获取课程列表接口描述（只保留分页，干净！）
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("course.list.summary"), queryPage, CourseQuery, CoursePageJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(Int32, "pageIndex", ZH_WORDS_GETTER("common.field.pageIndex"), 1, true);
		API_DEF_ADD_QUERY_PARAMS(Int32, "pageSize", ZH_WORDS_GETTER("common.field.pageSize"), 10, true);
		);

	// 3.2 定义获取课程列表接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7/workbench/courseList", queryPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, CourseQuery, queryParams);
	API_HANDLER_RESP_VO(execQueryPage(query));
		);

	//保存接口
	// 3.1 定义保存报名接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("course.saveReg.summary"), saveReg, Uint64JsonVO::Wrapper, API_TAG);
	// 3.2 定义保存报名接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c7/workbench/register", saveReg, BODY_DTO(CourseDTO::Wrapper, dto), execSave(dto, authObject->getPayload()));


private:
	
	CourseListJsonVO::Wrapper execQueryCourseDetail(const QueryParams& queryParams);
	CoursePageJsonVO::Wrapper execQueryPage(const CourseQuery::Wrapper& query);
	Uint64JsonVO::Wrapper execSave(const CourseDTO::Wrapper& dto, const PayloadDTO& payload);
};

#include OATPP_CODEGEN_END(ApiController)

#endif