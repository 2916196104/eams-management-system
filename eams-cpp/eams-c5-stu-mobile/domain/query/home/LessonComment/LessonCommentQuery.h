#pragma once


#ifndef _LESSONCOMMENT_QUERY_
#define _LESSONCOMMENT_QUERY_
#include "../../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class LessonCommentQuery : public PageQuery
{
	DTO_INIT(LessonCommentQuery, PageQuery);
	DTO_FIELD(Int64, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = ZH_WORDS_GETTER("LessonComment.field.student_id");
	}
};



#include OATPP_CODEGEN_END(DTO)
#endif