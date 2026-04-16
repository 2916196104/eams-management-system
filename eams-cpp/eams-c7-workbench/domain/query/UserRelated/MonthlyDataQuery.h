#pragma once
#ifndef _MONTHLYDATAQUERY_H_
#define _MONTHLYDATAQUERY_H_
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
*∞‡º∂≤È—Ø¿‡
*/
class MonthlyDataQuery : public PageQuery
{
	DTO_INIT(MonthlyDataQuery, PageQuery);
	//API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("select_teacher.name"));
};

#include OATPP_CODEGEN_END(DTO)

#endif

