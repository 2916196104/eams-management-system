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

// 1. 获取学员列表 (条件+分页)
PageDTO<TimetableStudentDTO::Wrapper>::Wrapper ClassStudentService::getStudentList(const StuListQuery::Wrapper& query)
{
	// 1. 定义分页对象
	auto page = PageDTO<TimetableStudentDTO::Wrapper>::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	// 2. 调用 DAO 获取总条数
	ClassStudentDAO dao;
	auto count = dao.count(query);
	if (count <= 0) return page; // 数据库没数据，直接返回空列表

	page->total = count;
	page->calcPages();

	// 3. 调用 DAO 获取当前页的真实数据
	auto list = dao.selectAll(query);

	// 4. 数据转换：DO -> DTO
	for (auto one : list)
	{
		auto dto = TimetableStudentDTO::createShared();
		// 将 DO 里查出来的 student_id 赋值给 DTO
		dto->id = std::to_string(one->getStudentId());

		dto->name = "真实的学员_" + std::to_string(one->getStudentId());
		dto->phone = "13800000000";
		dto->gender = "1";
		dto->rest_hour = 10;

		page->addData(dto);
	}
	return page;
}

// 2. 添加学员到课次
bool ClassStudentService::addStudentToLesson(const AddStudentToLessonDTO::Wrapper& dto)
{
	if (!dto->course_id || !dto->studentIds || dto->studentIds->size() == 0) {
		return false;
	}

	ClassStudentDAO dao;
	int64_t classId = std::stoll(dto->course_id.getValue("0"));

	uint64_t baseId = std::time(nullptr) * 1000;
	int index = 0;

	// 遍历前端传过来的所有学生 ID，批量插入数据库
	for (auto stuIdStr : *dto->studentIds) {
		auto doObj = std::make_shared<ClassStudentDO>();

		// 组装要插入的数据库对象
		doObj->setId(baseId + index);
		index++;
		doObj->setClassId(classId);
		doObj->setStudentId(std::stoll(stuIdStr.getValue("0")));
		doObj->setAddTime("2025-3-23 10:00:00");
		doObj->setDeleted(0);
		doObj->setCreator(0);
		doObj->setReason(0);
		doObj->setRemark("");
		doObj->setConsumeCourseId(0);

		// 调用 DAO 执行插入
		if (dao.insert(doObj) <= 0) {
			return false;
		}
	}
	return true;
}

// 3. 获取学员课程列表
oatpp::List<TimetableStudentCourseDTO::Wrapper> ClassStudentService::getStudentCourseList(const StuClassQuery::Wrapper& query)
{
	auto list = oatpp::List<TimetableStudentCourseDTO::Wrapper>::createShared();
	if (!query->id) return list;

	// 调用 DAO 查出这个学生报了哪些课
	ClassStudentDAO dao;
	auto doList = dao.selectByStudentId(query->id.getValue(""));

	for (auto one : doList) {
		auto dto = TimetableStudentCourseDTO::createShared();
		dto->course_id = std::to_string(one->getClassId());

		dto->title = "真实的课程_" + std::to_string(one->getClassId());
		dto->rest_hour = 0;

		list->push_back(dto);
	}
	return list;
}