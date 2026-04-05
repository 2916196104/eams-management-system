#pragma once
#ifndef _SELECTTEACHERQUERY_H_
#define _SELECTTEACHERQUERY_H_
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
*∞‡º∂≤È—Ø¿‡
*/
class SelectTeacherQuery : public PageQuery
{
	DTO_INIT(SelectTeacherQuery, PageQuery);
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("select_teacher.name"));
};

#include OATPP_CODEGEN_END(DTO)

#endif

