#ifndef __GET_COMMON_DATETIME_QUERY_H__
#define __GET_COMMON_DATETIME_QUERY_H__

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class GetCommonDatetimeQuery : public oatpp::DTO
{
	DTO_INIT(GetCommonDatetimeQuery, DTO);

	API_DTO_FIELD(String, date, "Lesson date", true, "2026-03-15");
	API_DTO_FIELD(UInt64, teacher_id, "Teacher ID", false, 1001);
};

#include OATPP_CODEGEN_END(DTO)

#endif
