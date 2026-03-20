#pragma once
#ifndef _CREDITEXCHANGELIST_QUERY_
#define _CREDITEXCHANGELIST_QUERY_

#include "../../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CreditexchangelistQuery : public PageQuery 
{
	DTO_INIT(CreditexchangelistQuery, PageQuery);
	DTO_FIELD(Int32, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = "student_id:::::::";
	}
};




#include OATPP_CODEGEN_END(DTO)

#endif // !_CREDITEXCHANGELIST_QUERY_