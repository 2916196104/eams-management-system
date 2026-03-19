#pragma once
#ifndef _CREDITMALLLIST_QUERY_
#define _CREDITMALLLIST_QUERY_

#include "../../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CreditmalllistQuery : public PageQuery
{
	DTO_INIT(CreditmalllistQuery, PageQuery);
	DTO_FIELD(Int32, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = "student_id:::::::";
	}
};




#include OATPP_CODEGEN_END(DTO)

#endif // !_CREDITMALLLIST_QUERY_