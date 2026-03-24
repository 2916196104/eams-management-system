#pragma once

#ifndef _LESSON_TEACHER_DO_
#define _LESSON_TEACHER_DO_

#include "DoInclude.h"

class LessonTeacherDO : public BaseDO {
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 课程id
	MYSQL_SYNTHESIZE(string, lesson_id, Lesson_id);
	// 老师id
	MYSQL_SYNTHESIZE(string, teacher_id, Teacher_id);
	// 课时费
	MYSQL_SYNTHESIZE(string, commission, Commission);
	// 1上课老师2助教
	MYSQL_SYNTHESIZE(int, type_num, Type_num);

public:
	LessonTeacherDO : BaseDO("lesson_teacher") {
		// 主键
		MYSQL_ADD_FIELD_PK("id", "s", id);
		// 课程id
		MYSQL_ADD_FIELD("lesson_id", "s", lesson_id);
		// 老师id
		MYSQL_ADD_FIELD("teacher_id", "s", teacher_id);
		// 课时费
		MYSQL_ADD_FIELD("commission", "s", commission);
		// 1上课老师2助教
		MYSQL_ADD_FIELD("type_num", "i", type_num);
	}
};

typedef std::shared_ptr<LessonTeacherDO> PtrLessonTeacherDO;

#endif