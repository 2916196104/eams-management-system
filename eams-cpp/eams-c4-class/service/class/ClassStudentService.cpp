#include "stdafx.h"
#include "ClassStudentService.h"
#include "dao/class/ClassStudentDAO.h"

ClassStudentPageDTO::Wrapper ClassStudentService::listClassStudents(const ClassStudentQuery::Wrapper& query)
{
	auto page = ClassStudentPageDTO::createShared();
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
		auto dto = ClassStudentDTO::createShared();
		dto->id = one->getId();
		dto->classId = one->getClassId();
		dto->studentId = one->getStudentId();
		dto->consumeCourseId = one->getConsumeCourseId();
		dto->reason = one->getReason();
		dto->addTime = one->getAddTime().c_str();
		dto->classStudentRemark = one->getClassStudentRemark().c_str();
		dto->studentName = one->getStudentName().c_str();
		dto->familyRel = one->getFamilyRel();
		dto->stage = one->getStage();
		dto->gender = one->getGender();
		dto->birthday = one->getBirthday().c_str();
		dto->headImg = one->getHeadImg().c_str();
		dto->userId = one->getUserId();
		dto->parentName = one->getParentName().c_str();
		dto->mobile = one->getMobile().c_str();
		dto->studentRemark = one->getStudentRemark().c_str();
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
	dto->reason = one->getReason();
	dto->addTime = one->getAddTime().c_str();
	dto->classStudentRemark = one->getClassStudentRemark().c_str();
	dto->className = one->getClassName().c_str();
	dto->classCourseId = one->getClassCourseId();
	dto->classCourseName = one->getClassCourseName().c_str();
	dto->gradeId = one->getGradeId();
	dto->gradeName = one->getGradeName().c_str();
	dto->userId = one->getUserId();
	dto->parentName = one->getParentName().c_str();
	dto->mobile = one->getMobile().c_str();
	dto->familyRel = one->getFamilyRel();
	dto->studentName = one->getStudentName().c_str();
	dto->stage = one->getStage();
	dto->gender = one->getGender();
	dto->birthday = one->getBirthday().c_str();
	dto->headImg = one->getHeadImg().c_str();
	dto->studentRemark = one->getStudentRemark().c_str();
	dto->countLessonRemaining = one->getCountLessonRemaining();
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
		dto->remark = one->getRemark().c_str();
		dto->countLessonTotal = one->getCountLessonTotal();
		dto->countLessonComplete = one->getCountLessonComplete();
		dto->countLessonRefund = one->getCountLessonRefund();
		dto->countLessonRemaining = one->getCountLessonRemaining();
		dto->courseAmount = one->getCourseAmount();
		dto->discountAmount = one->getDiscountAmount();
		dto->amount = one->getAmount();
		dto->paidAmount = one->getPaidAmount();
		dto->payOff = one->getPayOff();
		dto->operatorId = one->getOperatorId();
		dto->creator = one->getCreator();
		dto->addTime = one->getAddTime().c_str();
		dto->editor = one->getEditor();
		dto->editTime = one->getEditTime().c_str();
		dto->verifyState = one->getVerifyState();
		dto->warningTimes = one->getWarningTimes();
		dto->priority = one->getPriority();
		dto->unitPrice = one->getUnitPrice();
		dto->fromTrial = one->getFromTrial();
		dto->orgId = one->getOrgId();
		dto->defaultConsumeCourse = one->getDefaultConsumeCourse();
		page->addData(dto);
	}
	return page;
}
