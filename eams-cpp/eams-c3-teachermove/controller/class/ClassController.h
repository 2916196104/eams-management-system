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
#include "service/class/ClassService.h"

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
		API_DEF_ADD_QUERY_PARAMS(String, "teacher_id", ZH_WORDS_GETTER("class.teacher"), "", true);   // 
		API_DEF_ADD_TAG(API_TAG);
	}


	ENDPOINT(API_M_GET, "class/class-list", queryClassList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// Query
		API_HANDLER_QUERY_PARAM(userQuery, ClassQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryClassList(userQuery));
	}

	ENDPOINT_INFO(queryClassDetail) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("class.detail"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(ClassDetailJsonVO);
		API_DEF_ADD_QUERY_PARAMS(String, "class_id", ZH_WORDS_GETTER("class.detail"), "", true);
		API_DEF_ADD_TAG(API_TAG);
	}

	ENDPOINT(API_M_GET, "class/class-detail", queryClassDetail, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		auto classId = queryParams.get("class_id");
		API_HANDLER_RESP_VO(execQueryClassDetail(classId));
	}

	ENDPOINT_INFO(queryClassStudentList) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("class.studentList"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(ClassStudentPageJsonVO);
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(String, "class_id", ZH_WORDS_GETTER("classStudent.classId"), "", true);
		// API_DEF_ADD_QUERY_PARAMS(String, "student_name", ZH_WORDS_GETTER("classStudent.studentName"), "", false);
		API_DEF_ADD_TAG(API_TAG);
	}
 // 定义接口
	// 3.1 定义获取班级学员详情接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("class.endpoints.getStudentDetail.title"), getStudentDetail, StudentDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "studentId", ZH_WORDS_GETTER("class.endpoints.getStudentDetail.params.studentId"), "studentId", true);
	);
	// 3.2 定义获取班级学员详情接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET,"class/stu-detail", getStudentDetail, QUERIES(QueryParams, queryParams),
		auto studentId = queryParams.get("studentId");
		API_HANDLER_RESP_VO(execGetStudentDetail(studentId));
	);

	ENDPOINT(API_M_GET, "class/class-student-list", queryClassStudentList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(userQuery, ClassStudentQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryClassStudentList(userQuery));
	}
	// 3.1 定义获取班级学员课程列表接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("class.endpoints.getStudentCourseList.title"), getStudentCourseList, CoursePageJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(String, "studentId", ZH_WORDS_GETTER("class.endpoints.getStudentCourseList.params.studentId"), "studentId", true);
	);
	// 3.2 定义获取班级学员课程列表接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "class/stu-cs-list", getStudentCourseList, QUERIES(QueryParams, queryParams),
		auto studentId = queryParams.get("studentId");
		auto pageIndex = queryParams.get("pageIndex");
		auto pageSize = queryParams.get("pageSize");
		API_HANDLER_RESP_VO(execGetStudentCourseList(studentId, pageIndex, pageSize, authObject->getPayload()));
	);
private: 
	// 定义接口执行函数
	
	// 业务服务
	ClassService classService;
	
	ClassPageJsonVO::Wrapper execQueryClassList(const ClassQuery::Wrapper& query) {
		auto vo = ClassPageJsonVO::createShared();
		vo->data = classService.getClassList(query);
		vo->success(vo->data);
		return vo;
	}
	ClassDetailJsonVO::Wrapper execQueryClassDetail(const oatpp::String& classId) {
		auto vo = ClassDetailJsonVO::createShared();
		vo->data = classService.getClassDetail(classId);
		vo->success(vo->data);
		return vo;
	}
	ClassStudentPageJsonVO::Wrapper execQueryClassStudentList(const ClassStudentQuery::Wrapper& query) {
		auto vo = ClassStudentPageJsonVO::createShared();
		auto classId = query && query->class_id ? query->class_id : "";
		vo->data = classService.getClassStudentList(classId);
		vo->success(vo->data);
		return vo;
	}
	// 3.3 执行获取班级学员详情
	StudentDetailJsonVO::Wrapper execGetStudentDetail(const String& studentId);
	// 3.3 执行获取班级学员课程列表
	CoursePageJsonVO::Wrapper execGetStudentCourseList(const oatpp::String& studentId, const oatpp::String& pageIndex, const oatpp::String& pageSize, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif