#ifndef __GET_DETAIL_CS_DTO_H__
#define __GET_DETAIL_CS_DTO_H__

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class GetDetailCSDTO : public oatpp::DTO
{
	DTO_INIT(GetDetailCSDTO, DTO);

	API_DTO_FIELD(UInt64, lesson_id, "Lesson ID", true, 10002);
	API_DTO_FIELD(String, lesson_date, "Lesson date", true, "2026-02-28");
	API_DTO_FIELD(String, start_time, "Start time", true, "15:12");
	API_DTO_FIELD(String, end_time, "End time", true, "16:12");
	API_DTO_FIELD(UInt32, period_count, "Period count", true, static_cast<v_uint32>(1));
	API_DTO_FIELD(String, course_title, "Course title", true, "Piano Beginner");
	API_DTO_FIELD(String, teacher_name, "Teacher name", true, "Zhang San");
	API_DTO_FIELD(UInt32, normal_count, "Normal attendance count", true, static_cast<v_uint32>(0));
	API_DTO_FIELD(UInt32, leave_count, "Leave count", true, static_cast<v_uint32>(0));
	API_DTO_FIELD(UInt32, absent_count, "Absent count", true, static_cast<v_uint32>(0));
	API_DTO_FIELD(UInt32, makeup_count, "Makeup count", true, static_cast<v_uint32>(0));
	API_DTO_FIELD(Boolean, can_comment_after_class, "Can comment after class", true, true);
	API_DTO_FIELD(Boolean, can_add_student, "Can add student", true, true);
};

#include OATPP_CODEGEN_END(DTO)

#endif
