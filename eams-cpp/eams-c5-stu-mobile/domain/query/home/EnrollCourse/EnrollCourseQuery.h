#pragma once




#ifndef _ENROLLCOURSES_QUERY
#define _ENROLLCOURSES_QUERY
#include "../../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class EnrollCourseQuery : public PageQuery
{
	DTO_INIT(EnrollCourseQuery, PageQuery);
	DTO_FIELD(Int32, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = "";
	}
};






#include OATPP_CODEGEN_END(DTO)
#endif // !_EnrollCourses
