#pragma once
#ifndef _CUSTOMER_QUERY_
#define _CUSTOMER_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CustomerQuery : public PageQuery {
	DTO_INIT(CustomerQuery, PageQuery);
};

#include OATPP_CODEGEN_END(DTO)

#endif
