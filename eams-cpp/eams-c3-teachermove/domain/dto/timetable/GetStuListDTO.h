#ifndef __GET_STU_LIST_DTO_H__
#define __GET_STU_LIST_DTO_H__

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class StuListItemDTO : public oatpp::DTO
{
	DTO_INIT(StuListItemDTO, DTO);

	API_DTO_FIELD(UInt64, student_id, "Student ID", true, 70001);
	API_DTO_FIELD(String, student_name, "Student name", true, "Zhang Xiaoming");
	API_DTO_FIELD(String, consume_course, "Consumed course", true, "Piano Beginner");
	API_DTO_FIELD(Int32, attendance_state, "Attendance state", true, 0);
	API_DTO_FIELD(String, attendance_state_text, "Attendance state text", true, "Unsigned");
	API_DTO_FIELD(UInt32, signed_times, "Signed times", true, static_cast<v_uint32>(1));
	API_DTO_FIELD(UInt32, adjust_count, "Adjust count", true, static_cast<v_uint32>(1));
	API_DTO_FIELD(Boolean, can_change_course, "Can change course", true, true);
	API_DTO_FIELD(Boolean, can_leave, "Can leave", true, true);
	API_DTO_FIELD(Boolean, can_absent, "Can absent", true, true);
	API_DTO_FIELD(Boolean, can_sign, "Can sign", true, true);
};

class GetStuListDTO : public oatpp::DTO
{
	DTO_INIT(GetStuListDTO, DTO);

	API_DTO_FIELD(UInt64, lesson_id, "Lesson ID", true, 10002);
	API_DTO_FIELD(UInt64, page_index, "Page index", true, 1);
	API_DTO_FIELD(UInt64, page_size, "Page size", true, 10);
	API_DTO_FIELD(UInt64, total, "Total count", true, 2);
	API_DTO_FIELD(UInt64, total_page, "Total pages", true, 1);
	API_DTO_FIELD(List<StuListItemDTO::Wrapper>, records, "Student records", true, {});
};

#include OATPP_CODEGEN_END(DTO)

#endif
