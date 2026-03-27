#pragma once

#include "BaseDO.h"
#include "SqlHelper.h"

class LessonStudentDO : public BaseDO
{
public:
	LessonStudentDO() : BaseDO("lesson_student")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("lesson_id", "ll", lesson_id);
		MYSQL_ADD_FIELD("class_id", "i", class_id);
		MYSQL_ADD_FIELD("student_id", "ll", student_id);
		MYSQL_ADD_FIELD("dec_lesson_count", "i", dec_lesson_count);
		MYSQL_ADD_FIELD("lesson_count", "i", lesson_count);
		MYSQL_ADD_FIELD("teacher_id", "ll", teacher_id);
		MYSQL_ADD_FIELD("sign_time", "dt", sign_time);
		MYSQL_ADD_FIELD("sign_type", "i", sign_type);
		MYSQL_ADD_FIELD("sign_state", "i", sign_state);
		MYSQL_ADD_FIELD("score", "i", score);
		MYSQL_ADD_FIELD("evaluation", "s", evaluation);
		MYSQL_ADD_FIELD("evaluate_time", "dt", evaluate_time);
		MYSQL_ADD_FIELD("evaluate_teacher", "ll", evaluate_teacher);
		MYSQL_ADD_FIELD("consume_course_id", "ll", consume_course_id);
		MYSQL_ADD_FIELD("consume_student_course_id", "ll", consume_student_course_id);
		MYSQL_ADD_FIELD("counselor", "ll", counselor);
		MYSQL_ADD_FIELD("add_time", "dt", add_time);
		MYSQL_ADD_FIELD("org_id", "ll", org_id);
	}

public:
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(int64_t, lesson_id, LessonId);
	MYSQL_SYNTHESIZE(int32_t, class_id, ClassId);
	MYSQL_SYNTHESIZE(int64_t, student_id, StudentId);
	MYSQL_SYNTHESIZE(int32_t, dec_lesson_count, DecLessonCount);
	MYSQL_SYNTHESIZE(int32_t, lesson_count, LessonCount);
	MYSQL_SYNTHESIZE(int64_t, teacher_id, TeacherId);
	MYSQL_SYNTHESIZE(std::string, sign_time, SignTime);
	MYSQL_SYNTHESIZE(int32_t, sign_type, SignType);
	MYSQL_SYNTHESIZE(int32_t, sign_state, SignState);
	MYSQL_SYNTHESIZE(int32_t, score, Score);
	MYSQL_SYNTHESIZE(std::string, evaluation, Evaluation);
	MYSQL_SYNTHESIZE(std::string, evaluate_time, EvaluateTime);
	MYSQL_SYNTHESIZE(int64_t, evaluate_teacher, EvaluateTeacher);
	MYSQL_SYNTHESIZE(int64_t, consume_course_id, ConsumeCourseId);
	MYSQL_SYNTHESIZE(int64_t, consume_student_course_id, ConsumeStudentCourseId);
	MYSQL_SYNTHESIZE(int64_t, counselor, Counselor);
	MYSQL_SYNTHESIZE(std::string, add_time, AddTime);
	MYSQL_SYNTHESIZE(int64_t, org_id, OrgId);
};

using PtrLessonStudentDO = std::shared_ptr<LessonStudentDO>;