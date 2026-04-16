#pragma once

#include"../../GlobalInclude.h"
#include"domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class StclassRecordQuery :public PageQuery
{
	DTO_INIT(StclassRecordQuery, PageQuery);
};
#include OATPP_CODEGEN_END(DTO)