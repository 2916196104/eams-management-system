#pragma once

#ifndef _CLASSCONTROLLER_H_
#define _CLASSCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/class/ClassQuery.h"
#include "domain/dto/class/ClassDTO.h"
#include "domain/vo/class/ClassVO.h"
#include "Macros.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("class.tags.t1")

/**
 * 班级管理控制器，提供班级学员相关接口
 */
class ClassController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(ClassController);
public: // 定义接口
	// 3.1 定义获取班级学员详情接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("class.endpoints.getStudentDetail.title"), getStudentDetail, oatpp::Object<StudentDetailDTO>, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "studentId", ZH_WORDS_GETTER("class.endpoints.getStudentDetail.params.studentId"), "id", true);
	);
	// 3.2 定义获取班级学员详情接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/class/student/detail", getStudentDetail, QUERY(String, studentId), execGetStudentDetail(studentId));

	// 3.1 定义获取班级学员课程列表接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("class.endpoints.getStudentCourseList.title"), getStudentCourseList, CourseListQuery, oatpp::Object<CourseListResponseDTO>, API_TAG);
	// 3.2 定义获取班级学员课程列表接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/class/student/course/list", getStudentCourseList, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(courseQuery, CourseListQuery, queryParams); API_HANDLER_RESP_VO(execGetStudentCourseList(courseQuery, authObject->getPayload())););

private: // 定义接口执行函数
	// 3.3 执行获取班级学员详情
	oatpp::Object<StudentDetailDTO> execGetStudentDetail(const String& studentId);
	// 3.3 执行获取班级学员课程列表
	oatpp::Object<CourseListResponseDTO> execGetStudentCourseList(const oatpp::Object<CourseListQuery>& query, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif