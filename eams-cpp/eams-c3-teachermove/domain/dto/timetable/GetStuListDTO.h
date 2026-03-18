#ifndef __GET_STU_LIST_DTO_H__
#define __GET_STU_LIST_DTO_H__

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class GetStuListDTO : public oatpp::DTO
{
	DTO_INIT(GetStuListDTO, DTO);

	API_DTO_FIELD(UInt64, lesson_id, "Lesson ID", true, 10002);
	API_DTO_FIELD(UInt64, page_index, "Page index", true, 1);
	API_DTO_FIELD(UInt64, page_size, "Page size", true, 10);
	API_DTO_FIELD(UInt64, total, "Total count", true, 2);
	API_DTO_FIELD(UInt64, total_page, "Total pages", true, 1);
	API_DTO_FIELD(UInt64, student_id, "Student ID", true, 70001);
	API_DTO_FIELD(UInt32, unsigned_count, "Unsigned count", true, static_cast<v_uint32>(1));
	API_DTO_FIELD(Boolean, is_change_course, "Is change course", true, false);
	API_DTO_FIELD(Boolean, is_leave, "Is leave", true, false);
	API_DTO_FIELD(Boolean, is_absent, "Is absent", true, false);
	API_DTO_FIELD(Boolean, is_signed, "Is signed", true, true);
};

#include OATPP_CODEGEN_END(DTO)

#endif
