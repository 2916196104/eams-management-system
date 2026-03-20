#pragma once
#pragma once
#ifndef _COURSEQUERY_H_
#define _COURSEQUERY_H_
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 课程查询类
 */
class CourseQuery : public PageQuery
{
	DTO_INIT(CourseQuery, PageQuery);
	//课程名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("course.field.courseName"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_DTO_
