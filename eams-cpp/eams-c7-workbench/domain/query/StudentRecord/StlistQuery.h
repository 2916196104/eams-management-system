#pragma once
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class StlistQuery : public PageQuery
{
	DTO_INIT(StlistQuery,PageQuery);
	//姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("stList.query.telephone");
	}

	//电话号码
	DTO_FIELD(String, telephone);
	DTO_FIELD_INFO(telephone) {
		info->description = ZH_WORDS_GETTER("stList.query.telephone");
	}
};

#include OATPP_CODEGEN_END(DTO)