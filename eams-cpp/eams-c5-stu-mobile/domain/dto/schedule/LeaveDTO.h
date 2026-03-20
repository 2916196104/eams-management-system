#pragma once
#ifndef _LEAVE_DTO_
#define _LEAVE_DTO_
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class LeaveDTO : public oatpp::DTO
{
	DTO_INIT(LeaveDTO, DTO);
	DTO_FIELD(Int32, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("leave.field.id");
	};

	DTO_FIELD(String, add_time);
	DTO_FIELD_INFO(add_time) {
		info->description = ZH_WORDS_GETTER("leave.field.add_time");
	};

	DTO_FIELD(Int32, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = ZH_WORDS_GETTER("leave.field.student_id");
	};

	DTO_FIELD(Int32, lesson_id);
	DTO_FIELD_INFO(lesson_id) {
		info->description = ZH_WORDS_GETTER("leave.field.lesson_id");
	};

	DTO_FIELD(String, reason);
	DTO_FIELD_INFO(reason) {
		info->description = ZH_WORDS_GETTER("leave.field.reason");
	};

	DTO_FIELD(Int8, state);
	DTO_FIELD_INFO(state) {
		info->description = ZH_WORDS_GETTER("leave.field.state");
	};

	DTO_FIELD(Int32, verify_staff);
	DTO_FIELD_INFO(verify_staff) {
		info->description = ZH_WORDS_GETTER("leave.field.verify_staff");
	};

	DTO_FIELD(String, verify_time);
	DTO_FIELD_INFO(verify_time) {
		info->description = ZH_WORDS_GETTER("leave.field.verify_time");
	};

	DTO_FIELD(Int32, counselor);
	DTO_FIELD_INFO(counselor) {
		info->description = ZH_WORDS_GETTER("leave.field.counselor");
	};

	DTO_FIELD(Int32, school_id);
	DTO_FIELD_INFO(school_id) {
		info->description = ZH_WORDS_GETTER("leave.field.school_id");
	};
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_LEAVE_DTO_