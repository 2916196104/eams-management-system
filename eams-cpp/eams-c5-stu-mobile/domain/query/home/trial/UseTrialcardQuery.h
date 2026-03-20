#pragma once
#ifndef _USETRIALCARDQUERY_H_
#define _USETRIALCARDQUERY_H_
#include "../../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class UseTrialcardQuery :public PageQuery {
	DTO_INIT(UseTrialcardQuery, PageQuery);
	DTO_FIELD(Int32, course_id);
	DTO_FIELD_INFO(course_id) {
		info->description = "";
	}
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_USETRIALCARDQUERY_H_
