#pragma once
#ifndef _LESSON_QUERY_
#define _LESSON_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include "ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class LessonQuery : public PageQuery
{
	DTO_INIT(LessonQuery, PageQuery);

	// 是否为预约课
	API_DTO_FIELD_DEFAULT(Boolean, bookable, ZH_WORDS_GETTER("lesson.field.bookable"));

	// 查询日期
	API_DTO_FIELD_DEFAULT(String, date, ZH_WORDS_GETTER("lesson.field.date"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_LESSON_QUERY_