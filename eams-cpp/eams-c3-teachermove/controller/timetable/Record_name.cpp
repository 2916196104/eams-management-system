#include "stdafx.h"
#include "Record_name.h"
#include "service/timetable/RecordnameService.h"



GetDetailCSJsonVO::Wrapper Record_name::execGetDetailCS(const GetDetailCSQuery::Wrapper& query)
{
	RecordnameService service;
	return service.getDetailCS(query);
}

GetStuListJsonVO::Wrapper Record_name::execGetStuList(const GetStuListQuery::Wrapper& query)
{
	RecordnameService service;
	return service.getCSStuList(query);
}

SetStudyStatusRspJsonVO::Wrapper Record_name::updateModifyStatus(const SetStudyStatusDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回数据对象
	auto jvo = SetStudyStatusRspJsonVO::createShared();
	// 参数校验
	if (!dto->id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 执行数据修改
	dto->setPayload(&payload);
	/*if (SampleService().updateData(dto)) {
		jvo->success(dto->id);
	}
	else
	{
		jvo->fail(dto->id);
	}*/
	// 响应结果
	return jvo;
}

// Endpoint 1: Implementation of Get Student List (with conditions + pagination)
TimetableStudentPageJsonVO::Wrapper Record_name::execGetStuList(const StuListQuery::Wrapper& query, const PayloadDTO& payload)
{
	RecordnameService service;
	return service.getStudentList(query, payload);
}

// Endpoint 2: Implementation of Add Student to Lesson
StringJsonVO::Wrapper Record_name::execInsertStuToCS(const AddStudentToLessonDTO::Wrapper& dto, const PayloadDTO& payload)
{
	RecordnameService service;
	return service.insertStudentToCourse(dto, payload);
}

// Endpoint 3: Implementation of Get Student Course List
ListJsonVO<TimetableStudentCourseDTO::Wrapper>::Wrapper Record_name::execGetStuClassList(const StuClassQuery::Wrapper& query, const PayloadDTO& payload)
{
	RecordnameService service;
	return service.getStudentCourseList(query, payload);
}