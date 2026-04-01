#pragma once

#include "../../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class HomeworkListQuery :public PageQuery
{
	DTO_INIT(HomeworkListQuery, PageQuery);

};

#include OATPP_CODEGEN_END(DTO)