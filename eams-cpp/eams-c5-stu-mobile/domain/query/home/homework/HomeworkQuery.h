#pragma once
#ifndef _HOMEWORK_QUERY_
#define _HOMEWORK_QUERY_
#include "../../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class HomeworkQuery : public PageQuery
{
	DTO_INIT(HomeworkQuery, PageQuery);

	// 学生ID
	DTO_FIELD(Int64, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = "学生ID";
	}
};
#include OATPP_CODEGEN_END(DTO)
#endif