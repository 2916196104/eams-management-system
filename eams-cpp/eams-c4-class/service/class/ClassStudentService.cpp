#include "stdafx.h"
#include "ClassStudentService.h"
#include "dao/class/ClassStudentDAO.h"

namespace {
	int calcAge(const std::string& birthday)
	{
		if (birthday.size() < 10) return 0;
		int y = 0, m = 0, d = 0;
		if (sscanf(birthday.c_str(), "%d-%d-%d", &y, &m, &d) != 3) return 0;
		time_t t = time(nullptr);
		tm now {};
#ifdef _WIN32
		localtime_s(&now, &t);
#else
		now = *localtime(&t);
#endif
		int age = (now.tm_year + 1900) - y;
		if ((now.tm_mon + 1 < m) || ((now.tm_mon + 1 == m) && now.tm_mday < d)) {
			age--;
		}
		return age < 0 ? 0 : age;
	}
}

ClassStudentListPageDTO::Wrapper ClassStudentService::listClassStudents(const ClassStudentQuery::Wrapper& query)
{
	auto page = ClassStudentListPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	ClassStudentDAO dao;
	auto total = dao.countClassStudentList(query);
	page->total = total;
	page->calcPages();
	if (total <= 0) {
		return page;
	}

	auto list = dao.selectClassStudentList(query);
	for (const auto& one : list)
	{
		auto dto = ClassStudentListDTO::createShared();
		dto->id = one->getId();
		dto->classId = one->getClassId();
		dto->studentId = one->getStudentId();
		dto->studentName = one->getStudentName().c_str();
		dto->gender = one->getGender();
		dto->headImg = one->getHeadImg().c_str();
		dto->consumeCourseId = one->getConsumeCourseId();
		dto->countLessonRemaining = one->getCountLessonRemaining();
		page->addData(dto);
	}
	return page;
}

ClassStudentDetailDTO::Wrapper ClassStudentService::getClassStudentDetail(uint64_t id)
{
	ClassStudentDAO dao;
	auto one = dao.selectClassStudentDetail(id);
	if (!one)
		return nullptr;

	auto dto = ClassStudentDetailDTO::createShared();
	dto->id = one->getId();
	dto->classId = one->getClassId();
	dto->studentId = one->getStudentId();
	dto->consumeCourseId = one->getConsumeCourseId();
	dto->userId = one->getUserId();
	dto->name = one->getStudentName().c_str();
	dto->mobile = one->getMobile().c_str();
	dto->gender = one->getGender();
	dto->birthday = one->getBirthday().c_str();
	dto->age = calcAge(one->getBirthday());
	dto->stage = one->getStage();
	dto->headImg = one->getHeadImg().c_str();
	dto->remark = one->getStudentRemark().c_str();
	dto->classStudentRemark = one->getClassStudentRemark().c_str();
	return dto;
}

ClassStudentCoursePageDTO::Wrapper ClassStudentService::listClassStudentCourses(const ClassStudentCourseQuery::Wrapper& query)
{
	auto page = ClassStudentCoursePageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	ClassStudentDAO dao;
	auto total = dao.countClassStudentCourseList(query);
	page->total = total;
	page->calcPages();
	if (total <= 0) {
		return page;
	}

	auto list = dao.selectClassStudentCourseList(query);
	for (const auto& one : list)
	{
		auto dto = ClassStudentCourseDTO::createShared();
		dto->id = one->getId();
		dto->studentId = one->getStudentId();
		dto->courseId = one->getCourseId();
		dto->courseName = one->getCourseName().c_str();
		dto->subjectId = one->getSubjectId();
		dto->subjectName = one->getSubjectName().c_str();
		dto->startDate = one->getStartDate().c_str();
		dto->expireDate = one->getExpireDate().c_str();
		dto->countLessonTotal = one->getCountLessonTotal();
		dto->countLessonComplete = one->getCountLessonComplete();
		dto->countLessonRefund = one->getCountLessonRefund();
		dto->countLessonRemaining = one->getCountLessonRemaining();
		dto->defaultConsumeCourse = one->getDefaultConsumeCourse();
		dto->progress = (std::to_string(one->getCountLessonComplete()) + " / " + std::to_string(one->getCountLessonTotal())).c_str();
		page->addData(dto);
	}
	return page;
}
