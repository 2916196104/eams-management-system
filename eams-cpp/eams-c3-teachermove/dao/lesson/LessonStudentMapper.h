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

		lesson_student_do->setId(resultSet->getUInt64("id"));
		lesson_student_do->setLessonId(resultSet->getInt64("lesson_id"));
		lesson_student_do->setClassId(resultSet->getInt("class_id"));
		lesson_student_do->setStudentId(resultSet->getInt64("student_id"));
		lesson_student_do->setDecLessonCount(resultSet->getInt("dec_lesson_count"));
		lesson_student_do->setLessonCount(resultSet->getInt("lesson_count"));
		lesson_student_do->setTeacherId(resultSet->getInt64("teacher_id"));
		lesson_student_do->setSignTime(resultSet->getString("sign_time"));
		lesson_student_do->setSignState(resultSet->getInt("sign_state"));
		lesson_student_do->setScore(resultSet->getInt("score"));
		lesson_student_do->setEvaluateTime(resultSet->getString("evaluate_time"));
		lesson_student_do->setEvaluateTeacher(resultSet->getInt64("evaluate_teacher"));
		lesson_student_do->setConsumeCourseId(resultSet->getInt64("consume_course_id"));
		lesson_student_do->setConsumeStudentCourseId(resultSet->getInt64("consume_student_course_id"));
		lesson_student_do->setCounselor(resultSet->getInt64("counselor"));
		lesson_student_do->setAddTime(resultSet->getString("add_time"));
		lesson_student_do->setOrgId(resultSet->getInt64("org_id"));

		return lesson_student_do;
	}

	
};