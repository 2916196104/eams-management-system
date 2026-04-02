#pragma once
#ifndef _CLASS_STUDENT_DO_H_
#define _CLASS_STUDENT_DO_H_
#include "../../DoInclude.h"

class ClassStudentDO : public BaseDO
{
	MYSQL_SYNTHESIZE(int64_t, id, Id);
	MYSQL_SYNTHESIZE(int64_t, classId, ClassId);
	MYSQL_SYNTHESIZE(int64_t, studentId, StudentId);
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	MYSQL_SYNTHESIZE(int, reason, Reason);
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	MYSQL_SYNTHESIZE(string, remark, Remark);
	MYSQL_SYNTHESIZE(int64_t, consumeCourseId, ConsumeCourseId);

public:
	ClassStudentDO() : BaseDO("class_student")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD_NULLABLE("class_id", "ull", classId, false);
		MYSQL_ADD_FIELD_NULLABLE("student_id", "ull", studentId, false);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("creator", "ull", creator);
		MYSQL_ADD_FIELD("reason", "i", reason);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD_NULLABLE("consume_course_id", "ull", consumeCourseId, false);
	}
};

typedef std::shared_ptr<ClassStudentDO> PtrClassStudentDO;
#endif
