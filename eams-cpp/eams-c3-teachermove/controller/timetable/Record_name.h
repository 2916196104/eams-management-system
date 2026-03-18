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
	// Define controller access entry
	API_ACCESS_DECLARE(Record_name)
public:		// Define endpoints
	// Endpoint 1: Get student list (with conditions + pagination) - GetStuList

	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("timetable.endpoints.getStudentList.title"),
		GetStuList,
		StuListQuery,
		TimetableStudentPageJsonVO::Wrapper,
		ZH_WORDS_GETTER("timetable.tags.studentManage")
	)

		API_HANDLER_ENDPOINT_QUERY_AUTH(
			API_M_GET, "/timetable/student/list", GetStuList, StuListQuery,
			execGetStuList(query, authObject->getPayload())
		)

		// Endpoint 2: Add student to lesson - InsertStuToCS

		API_DEF_ENDPOINT_INFO_AUTH(
			ZH_WORDS_GETTER("timetable.endpoints.insertStuToCS.title"),
			InsertStuToCS,
			StringJsonVO::Wrapper,
			ZH_WORDS_GETTER("timetable.tags.studentManage"),
			API_DEF_NOTHING
		)

		API_HANDLER_ENDPOINT_AUTH(
			API_M_POST, "/timetable/student/add-to-cs", InsertStuToCS,
			BODY_DTO(AddStudentToLessonDTO::Wrapper, dto),
			execInsertStuToCS(dto, authObject->getPayload())
		)

		// Endpoint 3: Get student course list - GetStuClassList

		API_DEF_ENDPOINT_INFO_QUERY_AUTH(
			ZH_WORDS_GETTER("timetable.endpoints.getStudentCourseList.title"),
			GetStuClassList,
			StuClassQuery,
			ListJsonVO<TimetableStudentCourseDTO::Wrapper>::Wrapper,
			ZH_WORDS_GETTER("timetable.tags.studentManage")
		)

		API_HANDLER_ENDPOINT_QUERY_AUTH(
			API_M_GET, "/timetable/student/course-list", GetStuClassList, StuClassQuery,
			execGetStuClassList(query, authObject->getPayload())
		)

public:
	// Declare execution functions

	TimetableStudentPageJsonVO::Wrapper execGetStuList(const StuListQuery::Wrapper& query, const PayloadDTO& payload);

	StringJsonVO::Wrapper execInsertStuToCS(const AddStudentToLessonDTO::Wrapper& dto, const PayloadDTO& payload);

	ListJsonVO<TimetableStudentCourseDTO::Wrapper>::Wrapper execGetStuClassList(const StuClassQuery::Wrapper& query, const PayloadDTO& payload);

};

#include OATPP_CODEGEN_END(ApiController)
#endif
