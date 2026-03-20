#pragma once
#ifndef _GETTRIALCARDQUERY_H_
#define _GETTRIALCARDQUERY_H_
#include "../../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class GetTrialcardQuery :public PageQuery {
	DTO_INIT(GetTrialcardQuery, PageQuery);
	DTO_FIELD(Int32, course_id);
	DTO_FIELD_INFO(course_id) {
		info->description = "";
	}
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_GETTRIALCARDQUERY_H_
