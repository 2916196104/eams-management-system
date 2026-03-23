#pragma once
#ifndef _CLASS_STUDENT_MAPPER_H_
#define _CLASS_STUDENT_MAPPER_H_

#include "Mapper.h"
#include "domain/do/ClassStudentDO.h"

class UInt64Mapper : public Mapper<uint64_t>
{
public:
	uint64_t mapper(ResultSet* resultSet) const override
	{
		return resultSet->getUInt64(1);
	}
};

class ClassStudentListMapper : public Mapper<PtrClassStudentDO>
{
public:
	PtrClassStudentDO mapper(ResultSet* rs) const override
	{
		auto one = std::make_shared<ClassStudentDO>();
		one->setId(rs->getUInt64("id"));
		one->setClassId(rs->getUInt64("class_id"));
		one->setStudentId(rs->getUInt64("student_id"));
		one->setConsumeCourseId(rs->getUInt64("consume_course_id"));
		one->setReason(rs->getInt("reason"));
		one->setAddTime(rs->getString("add_time"));
		one->setClassStudentRemark(rs->getString("class_student_remark"));
		one->setUserId(rs->getUInt64("user_id"));
		one->setParentName(rs->getString("parent_name"));
		one->setMobile(rs->getString("mobile"));
		one->setFamilyRel(rs->getInt("family_rel"));
		one->setStudentName(rs->getString("student_name"));
		one->setStage(rs->getInt("stage"));
		one->setGender(rs->getInt("gender"));
		one->setBirthday(rs->getString("birthday"));
		one->setHeadImg(rs->getString("head_img"));
		one->setStudentRemark(rs->getString("student_remark"));
		one->setCountLessonRemaining(rs->getInt("count_lesson_remaining"));
		return one;
	}
};

class ClassStudentDetailMapper : public Mapper<PtrClassStudentDO>
{
public:
	PtrClassStudentDO mapper(ResultSet* rs) const override
	{
		auto one = ClassStudentListMapper().mapper(rs);
		one->setClassName(rs->getString("class_name"));
		one->setClassCourseId(rs->getUInt64("class_course_id"));
		one->setClassCourseName(rs->getString("class_course_name"));
		one->setGradeId(rs->getUInt64("grade_id"));
		one->setGradeName(rs->getString("grade_name"));
		return one;
	}
};

class ClassStudentCourseMapper : public Mapper<PtrClassStudentCourseDO>
{
public:
	PtrClassStudentCourseDO mapper(ResultSet* rs) const override
	{
		auto one = std::make_shared<ClassStudentCourseDO>();
		one->setId(rs->getUInt64("id"));
		one->setStudentId(rs->getUInt64("student_id"));
		one->setCourseId(rs->getUInt64("course_id"));
		one->setCourseName(rs->getString("course_name"));
		one->setSubjectId(rs->getUInt64("subject_id"));
		one->setSubjectName(rs->getString("subject_name"));
		one->setStartDate(rs->getString("start_date"));
		one->setExpireDate(rs->getString("expire_date"));
		one->setRemark(rs->getString("remark"));
		one->setCountLessonTotal(rs->getInt("count_lesson_total"));
		one->setCountLessonComplete(rs->getInt("count_lesson_complete"));
		one->setCountLessonRefund(rs->getInt("count_lesson_refund"));
		one->setCountLessonRemaining(rs->getInt("count_lesson_remaining"));
		one->setCourseAmount(rs->getDouble("course_amount"));
		one->setDiscountAmount(rs->getDouble("discount_amount"));
		one->setAmount(rs->getDouble("amount"));
		one->setPaidAmount(rs->getDouble("paid_amount"));
		one->setPayOff(rs->getInt("pay_off"));
		one->setOperatorId(rs->getUInt64("operator"));
		one->setCreator(rs->getUInt64("creator"));
		one->setAddTime(rs->getString("add_time"));
		one->setEditor(rs->getUInt64("editor"));
		one->setEditTime(rs->getString("edit_time"));
		one->setVerifyState(rs->getInt("verify_state"));
		one->setWarningTimes(rs->getInt("warning_times"));
		one->setPriority(rs->getInt("priority"));
		one->setUnitPrice(rs->getDouble("unit_price"));
		one->setFromTrial(rs->getInt("from_trial"));
		one->setOrgId(rs->getUInt64("org_id"));
		one->setDefaultConsumeCourse(rs->getInt("default_consume_course"));
		return one;
	}
};

#endif
