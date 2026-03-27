#pragma once
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class StlistQuery : public PageQuery
{
	DTO_INIT(StlistQuery, PageQuery);
	//姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("stlist.query.name");
	}

	//电话号码
	DTO_FIELD(String, mobile);
	DTO_FIELD_INFO(mobile) {
		info->description = ZH_WORDS_GETTER("stlist.query.mobile");
	}
};

#include OATPP_CODEGEN_END(DTO)