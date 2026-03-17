#pragma once


#ifndef __RECORD_NAME_H__
#define __RECORD_NAME_H__

#include "domain/GlobalInclude.h"
#include "domain/query/timetable/TimetableQuery.h"
#include "domain/dto//timetable/TimetableDTO.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)


class Record_name : public oatpp::web::server::api::ApiController 
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(Record_name)
public:		//定义接口
	// 接口 1: 获取学员列表(条件+分页) - GetStuList

	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		"获取学员列表",
		GetStuList,
		StuListQuery,
		TimetableStudentPageJsonVO::Wrapper,
		"学员管理模块"
	)

		API_HANDLER_ENDPOINT_QUERY_AUTH(
			API_M_GET, "/timetable/student/list", GetStuList, StuListQuery,
			execGetStuList(query, authObject->getPayload())
		)

		// 接口 2: 添加学员到课次 - InsertStuToCS

		API_DEF_ENDPOINT_INFO_AUTH(
			"添加学员到课次",
			InsertStuToCS,
			StringJsonVO::Wrapper,
			"学员管理模块",
			API_DEF_NOTHING
		)

		API_HANDLER_ENDPOINT_AUTH(
			API_M_POST, "/timetable/student/add-to-cs", InsertStuToCS,
			BODY_DTO(AddStudentToLessonDTO::Wrapper, dto),
			execInsertStuToCS(dto, authObject->getPayload())
		)

		// 接口 3: 获取学员课程列表 - GetStuClassList

		API_DEF_ENDPOINT_INFO_QUERY_AUTH(
			"获取学员课程列表",
			GetStuClassList,
			StuClassQuery,
			ListJsonVO<TimetableStudentCourseDTO::Wrapper>::Wrapper,
			"学员管理模块"
		)

		API_HANDLER_ENDPOINT_QUERY_AUTH(
			API_M_GET, "/timetable/student/course-list", GetStuClassList, StuClassQuery,
			execGetStuClassList(query, authObject->getPayload())
		)

public:
	// 声明执行函数

	TimetableStudentPageJsonVO::Wrapper execGetStuList(const StuListQuery::Wrapper& query, const PayloadDTO& payload);

	StringJsonVO::Wrapper execInsertStuToCS(const AddStudentToLessonDTO::Wrapper& dto, const PayloadDTO& payload);

	ListJsonVO<TimetableStudentCourseDTO::Wrapper>::Wrapper execGetStuClassList(const StuClassQuery::Wrapper& query, const PayloadDTO& payload);

};

#include OATPP_CODEGEN_END(ApiController)
#endif