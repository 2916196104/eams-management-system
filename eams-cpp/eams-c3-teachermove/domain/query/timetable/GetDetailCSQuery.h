#ifndef __GET_DETAIL_CS_QUERY_H__
#define __GET_DETAIL_CS_QUERY_H__

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class GetDetailCSQuery : public oatpp::DTO
{
	DTO_INIT(GetDetailCSQuery, DTO);

	API_DTO_FIELD(UInt64, lesson_id, "Lesson ID", true, 10002);
};

#include OATPP_CODEGEN_END(DTO)

#endif
