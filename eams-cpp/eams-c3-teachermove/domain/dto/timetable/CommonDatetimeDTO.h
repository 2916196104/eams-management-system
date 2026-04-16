#ifndef __COMMON_DATETIME_DTO_H__
#define __COMMON_DATETIME_DTO_H__

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CommonDatetimeLessonDTO : public oatpp::DTO
{
	DTO_INIT(CommonDatetimeLessonDTO, DTO);

	API_DTO_FIELD(UInt32, lesson_count, "Lesson count", true, 1);
	API_DTO_FIELD(String, start_time, "Start time", true, "15:12");
	API_DTO_FIELD(String, end_time, "End time", true, "16:12");
	API_DTO_FIELD(UInt64, teacher_id, "Teacher ID", true, 1001);
	API_DTO_FIELD(UInt64, classroom_id, "Classroom ID", false, 5001);
	API_DTO_FIELD(Boolean, is_signed, "Is signed", true, false);
	API_DTO_FIELD(Boolean, is_leave, "Is leave", true, false);
	API_DTO_FIELD(Boolean, is_reserved, "Is reserved", true, false);
};

class CommonDatetimeDTO : public oatpp::DTO
{
	DTO_INIT(CommonDatetimeDTO, DTO);

	API_DTO_FIELD(UInt32, lesson_count, "Lesson count", true, 3);
	API_DTO_FIELD(List<CommonDatetimeLessonDTO::Wrapper>, lessons, "Lesson list", true, {});
};

#include OATPP_CODEGEN_END(DTO)

#endif
