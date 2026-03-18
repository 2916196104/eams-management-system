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
 * �༶������������ṩ�༶ѧԱ��ؽӿ�
 */
class ClassController : public oatpp::web::server::api::ApiController
{
	// ����������������
	API_ACCESS_DECLARE(ClassController);
public:		
	ENDPOINT_INFO(queryClassList) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("class.list"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(ClassDetailPageJsonVO);
		// 
		API_DEF_ADD_PAGE_PARAMS();
		// 
		API_DEF_ADD_QUERY_PARAMS(String, "teacher_id", ZH_WORDS_GETTER("class.teacher"), "", true);   // 
	}


	ENDPOINT(API_M_GET, "/class/classList", queryClassList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// Query
		API_HANDLER_QUERY_PARAM(userQuery, ClassQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryClassList(userQuery));
	}

	ENDPOINT_INFO(queryClassDetail) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("class.detail"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(ClassDetailJsonVO);
		//// 
		//API_DEF_ADD_PAGE_PARAMS();
		// 
		API_DEF_ADD_QUERY_PARAMS(String, "teacher_id", ZH_WORDS_GETTER("class.teacher"), "", true);   // ID
 
	}

	ENDPOINT(API_M_GET, "/class/classDetail", queryClassDetail, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
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
		// API_DEF_ADD_QUERY_PARAMS(String, "student_name", ZH_WORDS_GETTER("classStudent.studentName"), "", false);
	}
 // ����ӿ�
	// 3.1 �����ȡ�༶ѧԱ����ӿ�����
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("class.endpoints.getStudentDetail.title"), getStudentDetail, oatpp::Object<StudentDetailDTO>, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("class.endpoints.getStudentDetail.params.studentName"), "name", false);
		API_DEF_ADD_QUERY_PARAMS(String, "phone", ZH_WORDS_GETTER("class.endpoints.getStudentDetail.params.phonenumber"), "phone", false);
	);
	// 3.2 �����ȡ�༶ѧԱ����ӿڴ���
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET,"/class/student/detail", getStudentDetail, QUERIES(QueryParams, queryParams),
		auto name = queryParams.get("name");
		auto phone = queryParams.get("phone");
		API_HANDLER_RESP_VO(execGetStudentDetail(name, phone));
	);

	ENDPOINT(API_M_GET, "/class/classStudentList", queryClassStudentList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(userQuery, ClassStudentQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryClassStudentList(userQuery));
	}
	// 3.1 定义获取班级学员课程列表接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("class.endpoints.getStudentCourseList.title"), getStudentCourseList, CoursePageJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_PAGE_PARAMS();
	);
	// 3.2 定义获取班级学员课程列表接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/class/student/course/list", getStudentCourseList, QUERIES(QueryParams, queryParams),
		auto pageIndex = queryParams.get("pageIndex");
		auto pageSize = queryParams.get("pageSize");
		API_HANDLER_RESP_VO(execGetStudentCourseList(pageIndex, pageSize, authObject->getPayload()));
	);
private: 
	// 定义接口执行函数
	
	ClassDetailPageJsonVO::Wrapper execQueryClassList(const ClassQuery::Wrapper& query) {
		return ClassDetailPageJsonVO::createShared();
	}
	ClassDetailJsonVO::Wrapper execQueryClassDetail(const ClassDTO::Wrapper& query) {
		return ClassDetailJsonVO::createShared();
	}
	ClassStudentPageJsonVO::Wrapper execQueryClassStudentList(const ClassStudentQuery::Wrapper& query) {
		return ClassStudentPageJsonVO::createShared();
	}
	// 3.3 执行获取班级学员详情
	oatpp::Object<StudentDetailDTO> execGetStudentDetail(const String& name, const String& phone);
	// 3.3 执行获取班级学员课程列表
	CoursePageJsonVO::Wrapper execGetStudentCourseList(const oatpp::String& pageIndex, const oatpp::String& pageSize, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif