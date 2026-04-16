#pragma once
#ifndef _CLASS_STUDENT_CONTROLLER_H_
#define _CLASS_STUDENT_CONTROLLER_H_

#include "ApiHelper.h"
#include "domain/query/class/ClassStudentQuery.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/class/ClassStudentVO.h"

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("class.tag")

class ClassStudentController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(ClassStudentController);
public:
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("class.queryClassStudentList.summary"), queryClassStudentList, ClassStudentQuery, ClassStudentListPageJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/c4class/queryClassStudentList", queryClassStudentList, ClassStudentQuery, execQueryClassStudentList(query));

	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("class.queryClassStudentDetail.summary"), queryClassStudentDetail, ClassStudentDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(UInt64, "id", ZH_WORDS_GETTER("class.field.classStudentId"), 8601, true);
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c4class/queryClassStudentDetail", queryClassStudentDetail, QUERY(UInt64, id), execQueryClassStudentDetail(id));

	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("class.queryClassStudentCourseList.summary"), queryClassStudentCourseList, ClassStudentCoursePageJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(UInt64, "classId", ZH_WORDS_GETTER("class.field.classId"), 8501, true);
		API_DEF_ADD_QUERY_PARAMS(UInt64, "studentId", ZH_WORDS_GETTER("class.field.studentId"), 8401, true);
		API_DEF_ADD_QUERY_PARAMS(String, "keyword", ZH_WORDS_GETTER("class.field.keyword"), "", false);
	);
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/c4class/queryClassStudentCourseList", queryClassStudentCourseList, ClassStudentCourseQuery, execQueryClassStudentCourseList(query));

private:
	ClassStudentListPageJsonVO::Wrapper execQueryClassStudentList(const ClassStudentQuery::Wrapper& query);
	ClassStudentDetailJsonVO::Wrapper execQueryClassStudentDetail(const oatpp::UInt64& id);
	ClassStudentCoursePageJsonVO::Wrapper execQueryClassStudentCourseList(const ClassStudentCourseQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif
