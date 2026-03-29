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
#include <algorithm>
#include <ctime>
#include <vector>

GetDetailCSJsonVO::Wrapper RecordnameService::getDetailCS(const GetDetailCSQuery::Wrapper& query)
{
	try
	{
		LessonStudentDao lessonStudentDao;
		uint64_t lessonId = query && query->lesson_id ? static_cast<uint64_t>(query->lesson_id.getValue(0)) : 0;
		auto data = GetDetailCSDTO::createShared();

		data->lesson_id = oatpp::UInt64(static_cast<v_uint64>(lessonId));
		data->lesson_date = "";
		data->start_time = "";
		data->end_time = "";
		data->period_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->course_title = "";
		data->teacher_name = "";

		auto totalCount = lessonId > 0 ? lessonStudentDao.CountLessonStudent(static_cast<int64_t>(lessonId)) : 0;
		data->normal_count = oatpp::UInt32(static_cast<v_uint32>(totalCount));
		data->leave_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->absent_count = oatpp::UInt32(static_cast<v_uint32>(0));
		data->makeup_count = oatpp::UInt32(static_cast<v_uint32>(0));

		data->can_comment_after_class = true;
		data->can_add_student = true;

		auto vo = GetDetailCSJsonVO::createShared();
		vo->success(data);
		return vo;
	}
	catch (const std::exception&)
	{
		auto vo = GetDetailCSJsonVO::createShared();
		vo->code = 500;
		vo->message = "getDetailCSFailed";
		return vo;
	}
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

	std::list<PtrClassStudentDO> records;
	std::vector<PtrClassStudentDO> filtered;
	if (query && query->keyword && !query->keyword->empty())
	{
		auto allQuery = StuListQuery::createShared();
		allQuery->pageIndex = 1;
		uint64_t totalAll = dao.count(query);
		allQuery->pageSize = totalAll == 0 ? 1 : totalAll;
		records = dao.selectAll(allQuery);

		const std::string keyword = query->keyword.getValue("");
		for (const auto& one : records)
		{
			if (std::to_string(one->getStudentId()).find(keyword) != std::string::npos)
			{
				filtered.push_back(one);
			}
		}

		pages->total = static_cast<v_int64>(filtered.size());
		pages->calcPages();

		const uint64_t offset = (pageIndex - 1) * pageSize;
		const uint64_t end = std::min<uint64_t>(offset + pageSize, filtered.size());
		for (uint64_t i = offset; i < end; ++i)
		{
			auto row = TimetableStudentDTO::createShared();
			row->id = std::to_string(filtered[i]->getStudentId());
			row->name = "";
			row->phone = "";
			row->gender = "";
			row->rest_hour = static_cast<v_int32>(0);
			pages->addData(row);
		}
	}
	else
	{
		pages->total = static_cast<v_int64>(dao.count(query));
		pages->calcPages();

		records = dao.selectAll(query);
		for (const auto& one : records)
		{
			auto row = TimetableStudentDTO::createShared();
			row->id = std::to_string(one->getStudentId());
			row->name = "";
			row->phone = "";
			row->gender = "";
			row->rest_hour = static_cast<v_int32>(0);
			pages->addData(row);
		}
	}

	jvo->success(pages);
	return jvo;
}

StringJsonVO::Wrapper RecordnameService::insertStudentToCourse(const AddStudentToLessonDTO::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();
	ClassStudentDAO dao;
	uint64_t successCount = 0;
	uint64_t duplicateCount = 0;
	uint64_t invalidCount = 0;
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
		// �������ݿ�ɽ��ܵ� datetime �ַ���������մ����²���ʧ�ܡ�
		std::time_t t = std::time(nullptr);
		std::tm tmNow;
#ifdef _WIN32
		localtime_s(&tmNow, &t);
#else
		localtime_r(&t, &tmNow);
#endif
		char timeBuf[20] = { 0 };
		std::strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", &tmNow);
		const std::string nowStr = timeBuf;

		for (const auto& sid : *dto->studentIds)
		{
			if (!sid || sid->empty())
			{
				++invalidCount;
				continue;
			}

			int64_t studentId = 0;
			try
			{
				studentId = std::stoll(sid.getValue("0"));
			}
			catch (...)
			{
				++invalidCount;
				continue;
			}

			// class_student �ϴ���(class_id, student_id)ΨһԼ�������� service �����ء�
			bool exists = false;
			auto boundRows = dao.selectByStudentId(std::to_string(studentId));
			for (const auto& row : boundRows)
			{
				if (row->getClassId() == classId)
				{
					exists = true;
					break;
				}
			}
			if (exists)
			{
				++duplicateCount;
				continue;
			}

			auto item = std::make_shared<ClassStudentDO>();
			item->setClassId(classId);
			item->setStudentId(studentId);
			item->setConsumeCourseId(classId);
			item->setReason(0);
			item->setDeleted(false);
			item->setRemark("");
			item->setAddTime(nowStr);

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

			auto affect = dao.insert(item);
			if (affect > 0)
			{
				successCount += affect;
			}
			else
			{
				++invalidCount;
			}
		}
	}

	if (successCount > 0)
	{
		jvo->success("successAdd:" + std::to_string(successCount)
			+ ",duplicate:" + std::to_string(duplicateCount)
			+ ",invalid:" + std::to_string(invalidCount));
	}
	else
	{
		jvo->code = 400;
		if (duplicateCount > 0 && invalidCount == 0)
		{
			jvo->message = "allDuplicate";
		}
		else
		{
			jvo->message = "paramIncomplete";
		}
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
	LessonDAO lessonDao;
	auto rows = dao.selectByStudentId(query->id.getValue(""));
	auto list = oatpp::List<TimetableStudentCourseDTO::Wrapper>::createShared();

	for (const auto& one : rows)
	{
		auto item = TimetableStudentCourseDTO::createShared();
		item->course_id = std::to_string(one->getConsumeCourseId());
		item->rest_hour = static_cast<v_int32>(0);

		// ���ȳ��԰� consume_course_id ��ȡ�δΣ�ʧ���� class_id ��ȡ�ð�����δΡ�
		PtrLessonDO lesson = nullptr;
		if (one->getConsumeCourseId() > 0)
		{
			lesson = lessonDao.selectById(static_cast<long long>(one->getConsumeCourseId()));
		}
		if (!lesson && one->getClassId() > 0)
		{
			auto lq = LessonQuery::createShared();
			lq->class_id = oatpp::String(std::to_string(one->getClassId()));
			lq->pageIndex = 1;
			lq->pageSize = 1;
			auto lessons = lessonDao.selectWithPage(lq);
			if (!lessons.empty())
			{
				item->title = lessons.front().getTitle();
				item->teacher_id = std::to_string(lessons.front().getTeacherId());
				item->sn = std::to_string(lessons.front().getSn());
			}
			else
			{
				item->title = "";
				item->teacher_id = "";
				item->sn = "";
			}
		}
		else if (lesson)
		{
			item->title = lesson->getTitle();
			item->teacher_id = std::to_string(lesson->getTeacherId());
			item->sn = std::to_string(lesson->getSn());
		}
		else
		{
			item->title = "";
			item->teacher_id = "";
			item->sn = "";
		}
		list->push_back(item);
	}

	jvo->success(list);
	return jvo;
}
