#pragma once
#ifndef _GETTRIALCARDLIST_QUERY_H_
#define _GETTRIALCARDLIST_QUERY_H_

#include "../../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class GetTrialCardListQuery : public PageQuery
{
	DTO_INIT(GetTrialCardListQuery, PageQuery);
	// ÐÕÃû
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("student.id");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // _GETTRIALCARDLIST_QUERY_H_