#include "stdafx.h"
#include "Record_name.h"
#include "service/timetable/RecordnameService.h"
#include "dao/class_student/ClassStudentDao.h"



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
	(void)payload;
	// Create outer response object VO
	auto jvo = TimetableStudentPageJsonVO::createShared();
	auto pages = PageDTO<TimetableStudentDTO::Wrapper>::createShared();
	pages->pageIndex = query && query->pageIndex ? query->pageIndex : oatpp::UInt64(1);
	pages->pageSize = query && query->pageSize ? query->pageSize : oatpp::UInt64(10);

	ClassStudentDAO dao;
	pages->total = static_cast<v_int64>(dao.count(query));
	pages->calcPages();

	auto records = dao.selectAll(query);
	for (const auto& one : records)
	{
		auto row = TimetableStudentDTO::createShared();
		row->id = std::to_string(one->getStudentId()).c_str();
		row->name = "";
		row->phone = "";
		row->gender = "";
		row->rest_hour = 0;
		pages->addData(row);
	}

	// Success response
	jvo->success(pages);
	return jvo;
}

// Endpoint 2: Implementation of Add Student to Lesson
StringJsonVO::Wrapper Record_name::execInsertStuToCS(const AddStudentToLessonDTO::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();
	ClassStudentDAO dao;
	uint64_t successCount = 0;
	int64_t classId = 0;
	if (dto && dto->course_id && !dto->course_id->empty())
	{
		try
		{
			classId = std::stoll(dto->course_id.getValue("0"));
		}
		catch (...)
		{
			classId = 0;
		}
	}

	if (dto && dto->studentIds)
	{
		for (const auto& sid : *dto->studentIds)
		{
			if (!sid || sid->empty())
			{
				continue;
			}

			int64_t studentId = 0;
			try
			{
				studentId = std::stoll(sid.getValue("0"));
			}
			catch (...)
			{
				continue;
			}

			auto item = std::make_shared<ClassStudentDO>();
			item->setClassId(classId);
			item->setStudentId(studentId);
			item->setConsumeCourseId(classId);
			item->setReason(0);
			item->setDeleted(false);
			item->setRemark("");
			item->setAddTime("");
			item->setCreator(payload.getId().empty() ? 0 : std::stoll(payload.getId()));

			successCount += dao.insert(item);
		}
	}

	if (successCount > 0) {
		jvo->success("successAdd");
	}
	else {
		jvo->code = 500;
		jvo->message = "paramIncomplete";
	}
	return jvo;
}

// Endpoint 3: Implementation of Get Student Course List
ListJsonVO<TimetableStudentCourseDTO::Wrapper>::Wrapper Record_name::execGetStuClassList(const StuClassQuery::Wrapper& query, const PayloadDTO& payload)
{
	(void)payload;
	auto jvo = ListJsonVO<TimetableStudentCourseDTO::Wrapper>::createShared();

	if (!query->id) {
		jvo->code = 500;
		jvo->message = "studentIdEmpty";
		return jvo;
	}

	ClassStudentDAO dao;
	auto rows = dao.selectByStudentId(query->id.getValue(""));
	auto list = oatpp::List<TimetableStudentCourseDTO::Wrapper>::createShared();
	for (const auto& one : rows)
	{
		auto item = TimetableStudentCourseDTO::createShared();
		item->course_id = std::to_string(one->getConsumeCourseId()).c_str();
		item->rest_hour = 0;
		item->title = "";
		item->teacher_id = "";
		item->sn = "";
		list->push_back(item);
	}

	// Success response
	jvo->success(list);
	return jvo;
}