/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/28

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "RecordnameService.h"
#include "dao/lesson/LessonDao.h"
#include "dao/lesson/LessonStudentDao.h"
#include "dao/class_student/ClassStudentDao.h"
#include "domain/query/lesson/LessonQuery.h"

GetDetailCSJsonVO::Wrapper RecordnameService::getDetailCS(const GetDetailCSQuery::Wrapper& query)
{
	LessonDAO lessonDao;
	LessonStudentDao lessonStudentDao;
	uint64_t lessonId = query && query->lesson_id ? static_cast<uint64_t>(query->lesson_id.getValue(0)) : 0;

	if (lessonId == 0)
	{
		auto latestQuery = LessonQuery::createShared();
		latestQuery->pageIndex = 1;
		latestQuery->pageSize = 1;
		auto latestRows = lessonDao.selectWithPage(latestQuery);
		if (!latestRows.empty())
		{
			lessonId = static_cast<uint64_t>(latestRows.front().getId());
		}
	}

	auto lesson = lessonId > 0 ? lessonDao.selectById(static_cast<long long>(lessonId)) : nullptr;
	auto data = GetDetailCSDTO::createShared();

	if (lesson)
	{
		data->lesson_id = oatpp::UInt64(static_cast<v_uint64>(lesson->getId()));
		data->lesson_date = lesson->getDate().c_str();
		data->start_time = lesson->getStartTime().c_str();
		data->end_time = lesson->getEndTime().c_str();
		data->period_count = oatpp::UInt32(static_cast<v_uint32>(lesson->getDecCount()));
		data->course_title = lesson->getTitle().c_str();
		data->teacher_name = std::to_string(lesson->getTeacherId()).c_str();
		auto totalCount = lessonStudentDao.CountLessonStudent(static_cast<int64_t>(lessonId));
		data->normal_count = oatpp::UInt32(static_cast<v_uint32>(totalCount));
		data->leave_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->absent_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->makeup_count = oatpp::UInt32(static_cast<v_uint32>(0));
	}
	else
	{
		data->lesson_id = oatpp::UInt64(static_cast<v_uint64>(lessonId));
		data->lesson_date = "";
		data->start_time = "";
		data->end_time = "";
		data->period_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->course_title = "";
		data->teacher_name = "";
		data->normal_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->leave_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->absent_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->makeup_count = oatpp::UInt32(static_cast<v_uint32>(0));
	}

	data->can_comment_after_class = true;
	data->can_add_student = true;

	auto vo = GetDetailCSJsonVO::createShared();
	vo->success(data);
	return vo;
}

GetStuListJsonVO::Wrapper RecordnameService::getCSStuList(const GetStuListQuery::Wrapper& query)
{
	LessonDAO lessonDao;
	LessonStudentDao lessonStudentDao;
	uint64_t lessonId = 0;
	auto latestQuery = LessonQuery::createShared();
	latestQuery->pageIndex = 1;
	latestQuery->pageSize = 1;
	auto latestRows = lessonDao.selectWithPage(latestQuery);
	if (!latestRows.empty())
	{
		lessonId = static_cast<uint64_t>(latestRows.front().getId());
	}

	uint64_t pageIndex = query && query->page_index ? query->page_index.getValue(1) : 1;
	uint64_t pageSize = query && query->page_size ? query->page_size.getValue(10) : 10;
	if (pageIndex == 0)
	{
		pageIndex = 1;
	}
	if (pageSize == 0)
	{
		pageSize = 10;
	}
	uint64_t total = lessonId > 0 ? lessonStudentDao.CountLessonStudent(static_cast<int64_t>(lessonId)) : 0;
	uint64_t totalPage = total == 0 ? 0 : (total + pageSize - 1) / pageSize;

	std::list<PtrLessonStudentDO> stuRows;
	if (lessonId > 0)
	{
		auto pageQuery = GetStuListQuery::createShared();
		pageQuery->page_index = pageIndex;
		pageQuery->page_size = pageSize;
		stuRows = lessonStudentDao.SelectLessonStudentWithPage(static_cast<int64_t>(lessonId), pageQuery);
	}

	auto data = GetStuListDTO::createShared();
	data->lesson_id = oatpp::UInt64(static_cast<v_uint64>(lessonId));
	data->page_index = oatpp::UInt64(static_cast<v_uint64>(pageIndex));
	data->page_size = oatpp::UInt64(static_cast<v_uint64>(pageSize));
	data->total = oatpp::UInt64(static_cast<v_uint64>(total));
	data->total_page = oatpp::UInt64(static_cast<v_uint64>(totalPage));

	if (!stuRows.empty())
	{
		auto& first = stuRows.front();
		data->student_id = oatpp::UInt64(static_cast<v_uint64>(first->getStudentId()));
		data->unsigned_count = oatpp::UInt32(static_cast<v_uint32>(first->getSignState() == 0 ? 1 : 0));
		data->is_change_course = false;
		data->is_leave = first->getSignState() == 2;
		data->is_absent = first->getSignState() == 3;
		data->is_signed = first->getSignState() != 0;
	}
	else
	{
		data->student_id = oatpp::UInt64(static_cast<v_uint64>(0));
		data->unsigned_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->is_change_course = false;
		data->is_leave = false;
		data->is_absent = false;
		data->is_signed = false;
	}

	auto vo = GetStuListJsonVO::createShared();
	vo->success(data);
	return vo;
}

TimetableStudentPageJsonVO::Wrapper RecordnameService::getStudentList(const StuListQuery::Wrapper& query, const PayloadDTO& payload)
{
	(void)payload;
	auto jvo = TimetableStudentPageJsonVO::createShared();
	auto pages = PageDTO<TimetableStudentDTO::Wrapper>::createShared();

	uint64_t pageIndex = query && query->pageIndex ? query->pageIndex.getValue(1) : 1;
	uint64_t pageSize = query && query->pageSize ? query->pageSize.getValue(10) : 10;
	if (pageIndex == 0)
	{
		pageIndex = 1;
	}
	if (pageSize == 0)
	{
		pageSize = 10;
	}

	pages->pageIndex = oatpp::UInt64(static_cast<v_uint64>(pageIndex));
	pages->pageSize = oatpp::UInt64(static_cast<v_uint64>(pageSize));

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
		row->rest_hour = static_cast<v_int32>(0);
		pages->addData(row);
	}

	jvo->success(pages);
	return jvo;
}

StringJsonVO::Wrapper RecordnameService::insertStudentToCourse(const AddStudentToLessonDTO::Wrapper& dto, const PayloadDTO& payload)
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

			int64_t creator = 0;
			if (!payload.getId().empty())
			{
				try
				{
					creator = std::stoll(payload.getId());
				}
				catch (...)
				{
					creator = 0;
				}
			}
			item->setCreator(creator);

			successCount += dao.insert(item);
		}
	}

	if (successCount > 0)
	{
		jvo->success("successAdd");
	}
	else
	{
		jvo->code = 500;
		jvo->message = "paramIncomplete";
	}

	return jvo;
}

ListJsonVO<TimetableStudentCourseDTO::Wrapper>::Wrapper RecordnameService::getStudentCourseList(const StuClassQuery::Wrapper& query, const PayloadDTO& payload)
{
	(void)payload;
	auto jvo = ListJsonVO<TimetableStudentCourseDTO::Wrapper>::createShared();

	if (!query || !query->id || query->id->empty())
	{
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
		item->rest_hour = static_cast<v_int32>(0);
		item->title = "";
		item->teacher_id = "";
		item->sn = "";
		list->push_back(item);
	}

	jvo->success(list);
	return jvo;
}
