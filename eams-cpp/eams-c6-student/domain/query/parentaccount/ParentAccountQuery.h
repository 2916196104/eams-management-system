#pragma once
#ifndef _PARENT_ACCOUNT_QUERY_H_
#define _PARENT_ACCOUNT_QUERY_H_

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include "ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(DTO)


class ParentAccountQuery : public PageQuery
{
	DTO_INIT(ParentAccountQuery, PageQuery);

	API_DTO_FIELD_DEFAULT(String, keyword, ZH_WORDS_GETTER("parentaccount.field.parent.keyword"));
	API_DTO_FIELD_DEFAULT(String, wxName, ZH_WORDS_GETTER("parentaccount.field.parent.wx-name"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_PARENT_ACCOUNT_QUERY_H_
