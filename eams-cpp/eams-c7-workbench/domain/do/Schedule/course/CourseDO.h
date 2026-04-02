#pragma once
#ifndef _COURSE_DO_H_
#define _COURSE_DO_H_
#include "../../DoInclude.h"

class CourseDO : public BaseDO
{
	MYSQL_SYNTHESIZE(int64_t, id, Id);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(int64_t, subjectId, SubjectId);

public:
	CourseDO() : BaseDO("course")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD("subject_id", "ull", subjectId);
	}
};

typedef std::shared_ptr<CourseDO> PtrCourseDO;
#endif
