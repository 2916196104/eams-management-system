#pragma once

#ifndef _CLASSCONTROLLER_H_
#define _CLASSCONTROLLER_H_


#include "domain/dto/class/ClassDTO.h"
#include "domain/vo/class/ClassVO.h"
#include "Macros.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include "domain/GlobalInclude.h"
#include "domain/vo/class/ClassStudentVO.h"
#include "domain/query/class/ClassQuery.h"
#include "domain/query/class/ClassStudentQuery.h"

using namespace oatpp;
using namespace oatpp::web;
using namespace oatpp::web::server;
using namespace oatpp::web::server::api;
using namespace oatpp::web::protocol::http;

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("class.tags.t1")

/**
 * 班级管理控制器，提供班级学员相关接口
 */
class ClassController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
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
		API_DEF_ADD_TAG(API_TAG);
	}


	ENDPOINT(API_M_GET, "class/classList", queryClassList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
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
		API_DEF_ADD_TAG(API_TAG);
	}

	ENDPOINT(API_M_GET, "class/classdetail", queryClassDetail, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
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
		API_DEF_ADD_QUERY_PARAMS(String, "class_id", ZH_WORDS_GETTER("class.classStudent.classId"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "student_name", ZH_WORDS_GETTER("class.classStudent.studentName"), "", false);
		API_DEF_ADD_TAG(API_TAG);
	}
 // 定义接口
	// 3.1 定义获取班级学员详情接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("class.endpoints.getStudentDetail.title"), getStudentDetail, oatpp::Object<StudentDetailDTO>, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "studentId", ZH_WORDS_GETTER("class.endpoints.getStudentDetail.params.studentId"), "id", true);
	);
	// 3.2 定义获取班级学员详情接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/class/student/detail", getStudentDetail, QUERY(String, studentId), execGetStudentDetail(studentId));

	ENDPOINT(API_M_GET, "/classStudentList", queryClassStudentList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME){
		API_HANDLER_QUERY_PARAM(userQuery, ClassStudentQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryClassStudentList(userQuery));
	}
	// 3.1 定义获取班级学员课程列表接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("class.endpoints.getStudentCourseList.title"), getStudentCourseList, CourseListQuery, oatpp::Object<CourseListResponseDTO>, API_TAG);
	// 3.2 定义获取班级学员课程列表接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/class/student/course/list", getStudentCourseList, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(courseQuery, CourseListQuery, queryParams); API_HANDLER_RESP_VO(execGetStudentCourseList(courseQuery, authObject->getPayload()));
	);
private: 
	// 定义接口执行函数
	ClassPageJsonVO::Wrapper execQueryClassList(const ClassQuery::Wrapper& query) {
		return ClassPageJsonVO::createShared();
	}
	ClassVO::Wrapper execQueryClassDetail(const ClassDTO::Wrapper& query) {
		return ClassVO::createShared();
	}
	ClassStudentPageJsonVO::Wrapper execQueryClassStudentList(const ClassStudentQuery::Wrapper& query) {
		return ClassStudentPageJsonVO::createShared();
	}
	// 3.3 执行获取班级学员详情
	oatpp::Object<StudentDetailDTO> execGetStudentDetail(const String& studentId);
	// 3.3 执行获取班级学员课程列表
	oatpp::Object<CourseListResponseDTO> execGetStudentCourseList(const oatpp::Object<CourseListQuery>& query, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif