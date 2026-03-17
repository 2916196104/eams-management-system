#ifndef __GET_STU_LIST_QUERY_H__
#define __GET_STU_LIST_QUERY_H__

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class GetStuListQuery : public oatpp::DTO
{
	DTO_INIT(GetStuListQuery, DTO);

	API_DTO_FIELD(UInt64, page_index, "Page index", false, 1);
	API_DTO_FIELD(UInt64, page_size, "Page size", false, 10);
};

#include OATPP_CODEGEN_END(DTO)

#endif
