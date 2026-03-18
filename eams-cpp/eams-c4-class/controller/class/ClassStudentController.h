#pragma once
#ifndef _CLASS_STUDENT_CONTROLLER_H_
#define _CLASS_STUDENT_CONTROLLER_H_

#include "domain/query/class/ClassStudentQuery.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/class/ClassStudentVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("class.tag")

class ClassStudentController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(ClassStudentController);
public:
	ENDPOINT_INFO(queryClassStudentList) {
		info->summary = ZH_WORDS_GETTER("class.query-class-student-list.summary");
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_RSP_JSON(ClassStudentPageJsonVO::Wrapper);
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(UInt64, "classId", ZH_WORDS_GETTER("class.field.classId"), 1, true);
		API_DEF_ADD_QUERY_PARAMS(String, "keyword", ZH_WORDS_GETTER("class.field.keyword"), "zhang", false);
	}
	ENDPOINT(API_M_GET, "/class/query-class-student-list", queryClassStudentList,
		QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, ClassStudentQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryClassStudentList(query));
	}

	ENDPOINT_INFO(queryClassStudentDetail) {
		info->summary = ZH_WORDS_GETTER("class.query-class-student-detail.summary");
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_RSP_JSON(ClassStudentDetailJsonVO::Wrapper);
		API_DEF_ADD_QUERY_PARAMS(UInt64, "id", ZH_WORDS_GETTER("class.field.classStudentId"), 1, true);
	}
	ENDPOINT(API_M_GET, "/class/query-class-student-detail", queryClassStudentDetail,
		QUERY(UInt64, id), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(execQueryClassStudentDetail(id));
	}

	ENDPOINT_INFO(queryClassStudentCourseList) {
		info->summary = ZH_WORDS_GETTER("class.query-class-student-course-list.summary");
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_RSP_JSON(ClassStudentCoursePageJsonVO::Wrapper);
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(UInt64, "classId", ZH_WORDS_GETTER("class.field.classId"), 1, true);
		API_DEF_ADD_QUERY_PARAMS(UInt64, "studentId", ZH_WORDS_GETTER("class.field.studentId"), 1, true);
		API_DEF_ADD_QUERY_PARAMS(String, "keyword", ZH_WORDS_GETTER("class.field.keyword"), "math", false);
	}
	ENDPOINT(API_M_GET, "/class/query-class-student-course-list", queryClassStudentCourseList,
		QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, ClassStudentCourseQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryClassStudentCourseList(query));
	}

private:
	ClassStudentPageJsonVO::Wrapper execQueryClassStudentList(const ClassStudentQuery::Wrapper& query);
	ClassStudentDetailJsonVO::Wrapper execQueryClassStudentDetail(const oatpp::UInt64& id);
	ClassStudentCoursePageJsonVO::Wrapper execQueryClassStudentCourseList(const ClassStudentCourseQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif