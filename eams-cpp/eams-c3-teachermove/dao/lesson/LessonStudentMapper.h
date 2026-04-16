#pragma once

#include <memory>

#include "Mapper.h"
#include "domain/do/lesson/LessonStudentDO.h"

class LessonStudentMapper : public Mapper<PtrLessonStudentDO>
{
public:
	PtrLessonStudentDO mapper(ResultSet* resultSet) const override
	{
		PtrLessonStudentDO lesson_student_do = std::make_shared<LessonStudentDO>();

		if (!resultSet->isNull("id")) lesson_student_do->setId(resultSet->getUInt64("id"));
		if (!resultSet->isNull("lesson_id")) lesson_student_do->setLessonId(resultSet->getInt64("lesson_id"));
		if (!resultSet->isNull("class_id")) lesson_student_do->setClassId(resultSet->getInt("class_id"));
		if (!resultSet->isNull("student_id")) lesson_student_do->setStudentId(resultSet->getInt64("student_id"));
		if (!resultSet->isNull("dec_lesson_count")) lesson_student_do->setDecLessonCount(resultSet->getInt("dec_lesson_count"));
		if (!resultSet->isNull("lesson_count")) lesson_student_do->setLessonCount(resultSet->getInt("lesson_count"));
		if (!resultSet->isNull("teacher_id")) lesson_student_do->setTeacherId(resultSet->getInt64("teacher_id"));
		if (!resultSet->isNull("sign_time")) lesson_student_do->setSignTime(resultSet->getString("sign_time"));
		if (!resultSet->isNull("sign_type")) lesson_student_do->setSignType(resultSet->getInt("sign_type"));
		if (!resultSet->isNull("sign_state")) lesson_student_do->setSignState(resultSet->getInt("sign_state"));
		if (!resultSet->isNull("score")) lesson_student_do->setScore(resultSet->getInt("score"));
		if (!resultSet->isNull("evaluation")) lesson_student_do->setEvaluation(resultSet->getString("evaluation"));
		if (!resultSet->isNull("evaluate_time")) lesson_student_do->setEvaluateTime(resultSet->getString("evaluate_time"));
		if (!resultSet->isNull("evaluate_teacher")) lesson_student_do->setEvaluateTeacher(resultSet->getInt64("evaluate_teacher"));
		if (!resultSet->isNull("consume_course_id")) lesson_student_do->setConsumeCourseId(resultSet->getInt64("consume_course_id"));
		if (!resultSet->isNull("consume_student_course_id")) lesson_student_do->setConsumeStudentCourseId(resultSet->getInt64("consume_student_course_id"));
		if (!resultSet->isNull("counselor")) lesson_student_do->setCounselor(resultSet->getInt64("counselor"));
		if (!resultSet->isNull("add_time")) lesson_student_do->setAddTime(resultSet->getString("add_time"));
		if (!resultSet->isNull("org_id")) lesson_student_do->setOrgId(resultSet->getInt64("org_id"));

		return lesson_student_do;
	}
};