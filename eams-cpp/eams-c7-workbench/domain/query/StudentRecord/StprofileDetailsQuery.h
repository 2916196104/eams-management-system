#pragma once


#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)


class StprofileDetailsQuery :public PageQuery
{
	DTO_INIT(StprofileDetailsQuery, PageQuery);
};
#include OATPP_CODEGEN_END(DTO)

