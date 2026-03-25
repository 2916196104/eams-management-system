#include "stdafx.h"
#include "RecordnameService.h"
#include "dao/class_student/ClassStudentDAO.h"

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

	// 遍历前端传过来的所有学生 ID，批量插入数据库
	for (auto stuIdStr : *dto->studentIds) {
		auto doObj = std::make_shared<ClassStudentDO>();

		// 组装要插入的数据库对象
		doObj->setClassId(classId);
		doObj->setStudentId(std::stoll(stuIdStr.getValue("0")));
		doObj->setAddTime("2025-3-23 10:00:00");
		doObj->setDeleted(0);

		// 调用 DAO 执行插入
		dao.insert(doObj);
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