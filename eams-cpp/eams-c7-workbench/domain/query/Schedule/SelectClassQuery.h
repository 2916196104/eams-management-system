#pragma once
#ifndef _SELECTCLASSQUERY_H_
#define _SELECTCLASSQUERY_H_
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
*∞‡º∂≤È—Ø¿‡
*/
class SelectClassQuery : public PageQuery
{
	DTO_INIT(SelectClassQuery, PageQuery);
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("select_class.name"));
};

#include OATPP_CODEGEN_END(DTO)

#endif

