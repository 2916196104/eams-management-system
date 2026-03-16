#pragma once


#ifndef _CLASSCONTROLLER_H_
#define _CLASSCONTROLLER_H_

#include "oatpp/web/server/api/ApiController.hpp"
#include "domain/GlobalInclude.h"
#include "domain/vo/class/ClassVO.h"
#include "domain/vo/class/ClassStudentVO.h"
#include "domain/query/class/ClassQuery.h"
#include "domain/query/class/ClassStudentQuery.h"
#include OATPP_CODEGEN_BEGIN(ApiController)


class ClassController : public oatpp::web::server::api::ApiController
{
	
	API_ACCESS_DECLARE(ClassController);
public:		
	ENDPOINT_INFO(queryClassList) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("class.list"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(ClassPageJsonVO);
		// 
		API_DEF_ADD_PAGE_PARAMS();
		// 
		API_DEF_ADD_QUERY_PARAMS(String, "teacher_id", ZH_WORDS_GETTER("class.teacher"), "", false);   // 
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("class.name"), "", false);             // 
		API_DEF_ADD_QUERY_PARAMS(String, "course_id", ZH_WORDS_GETTER("class.course"), "", false);     // 
		API_DEF_ADD_QUERY_PARAMS(String, "school_id", ZH_WORDS_GETTER("class.school"), "", false);     // 
		API_DEF_ADD_QUERY_PARAMS(String, "org_id", ZH_WORDS_GETTER("class.org"), "", false);           // 
		API_DEF_ADD_QUERY_PARAMS(String, "be_over", ZH_WORDS_GETTER("class.beOver"), "", false);      
	}


	ENDPOINT(API_M_GET, "/classList", queryClassList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// Query
		API_HANDLER_QUERY_PARAM(userQuery, ClassQuery, queryParams);
		// 
		API_HANDLER_RESP_VO(execQueryClassList(userQuery));
	}

	ENDPOINT_INFO(queryClassDetail) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("class.detail"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(ClassVO);
		//// 
		//API_DEF_ADD_PAGE_PARAMS();
		// 
		API_DEF_ADD_QUERY_PARAMS(String, "teacher_id", ZH_WORDS_GETTER("class.teacher"), "", true);   // ID
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("class.name"), "", false);             // 
		API_DEF_ADD_QUERY_PARAMS(String, "course_id", ZH_WORDS_GETTER("class.course"), "", false);     // 
		API_DEF_ADD_QUERY_PARAMS(String, "school_id", ZH_WORDS_GETTER("class.school"), "", false);     // ID
		API_DEF_ADD_QUERY_PARAMS(String, "org_id", ZH_WORDS_GETTER("class.org"), "", false);           // ID
		API_DEF_ADD_QUERY_PARAMS(String, "be_over", ZH_WORDS_GETTER("class.beOver"), "", false);      // 0 1 
	}

	ENDPOINT(API_M_GET, "/classdetail", queryClassDetail, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// Qu
		API_HANDLER_QUERY_PARAM(userQuery, ClassDTO, queryParams);
		//
		API_HANDLER_RESP_VO(execQueryClassDetail(userQuery));
	}

	ENDPOINT_INFO(queryClassStudentList) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("class.studentList"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(ClassStudentPageJsonVO);
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(String, "class_id", ZH_WORDS_GETTER("classStudent.classId"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "student_name", ZH_WORDS_GETTER("classStudent.studentName"), "", false);
	}

	ENDPOINT(API_M_GET, "/classStudentList", queryClassStudentList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(userQuery, ClassStudentQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryClassStudentList(userQuery));
	}

private:	
	ClassPageJsonVO::Wrapper execQueryClassList(const ClassQuery::Wrapper& query) {
		return ClassPageJsonVO::createShared();
	}
	ClassVO::Wrapper execQueryClassDetail(const ClassDTO::Wrapper& query) {
		return ClassVO::createShared();
	}
	ClassStudentPageJsonVO::Wrapper execQueryClassStudentList(const ClassStudentQuery::Wrapper& query) {
		return ClassStudentPageJsonVO::createShared();
	}
};

#include OATPP_CODEGEN_END(ApiController)

#endif