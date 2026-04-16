#pragma once
#ifndef _LESSON_TEACHER_DO_H_
#define _LESSON_TEACHER_DO_H_
#include "../../DoInclude.h"

/**
 * 课程教师关联数据库实体类
 */
class LessonTeacherDO : public BaseDO
{
	// 编号（主键）
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 课程id
	MYSQL_SYNTHESIZE(int64_t, lessonId, LessonId);
	// 教师id
	MYSQL_SYNTHESIZE(int64_t, teacherId, TeacherId);
	// 课时费
	MYSQL_SYNTHESIZE(double, commission, Commission);
	// 1上课老师2助教
	MYSQL_SYNTHESIZE(int, typeNum, TypeNum);

public:
	LessonTeacherDO() : BaseDO("lesson_teacher")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD_NULLABLE("lesson_id", "ll", lessonId, false);
		MYSQL_ADD_FIELD_NULLABLE("teacher_id", "ll", teacherId, false);
		MYSQL_ADD_FIELD_NULLABLE("commission", "d", commission, true);
		MYSQL_ADD_FIELD_NULLABLE("type_num", "i", typeNum, false);
	}
};

// 给LessonTeacherDO智能指针设定一个别名方便使用
typedef std::shared_ptr<LessonTeacherDO> PtrLessonTeacherDO;

#endif // !_LESSON_TEACHER_DO_H_
