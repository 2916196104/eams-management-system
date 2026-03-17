#ifndef __COMMON_DATETIME_DTO_H__
#define __COMMON_DATETIME_DTO_H__

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CommonDatetimeLessonDTO : public oatpp::DTO
{
	DTO_INIT(CommonDatetimeLessonDTO, DTO);

	API_DTO_FIELD(UInt64, id, "Lesson ID", true, 10001);
	API_DTO_FIELD(UInt64, class_id, "Class ID", true, 20001);
	API_DTO_FIELD(String, class_name, "Class name", true, "PE Class 1");
	API_DTO_FIELD(UInt64, course_id, "Course ID", true, 30001);
	API_DTO_FIELD(String, title, "Course title", true, "Taekwondo Experience");
	API_DTO_FIELD(String, date, "Lesson date", true, "2026-03-15");
	API_DTO_FIELD(String, start_time, "Start time", true, "09:00:00");
	API_DTO_FIELD(String, end_time, "End time", true, "10:00:00");
	API_DTO_FIELD(Int32, state, "Lesson state", true, 2);
	API_DTO_FIELD(String, state_text, "Lesson state text", true, "Finished");
	API_DTO_FIELD(UInt64, teacher_id, "Teacher ID", true, 1001);
	API_DTO_FIELD(String, teacher_name, "Teacher name", true, "Zhang San");
	API_DTO_FIELD(UInt64, classroom_id, "Classroom ID", false, 5001);
	API_DTO_FIELD(String, classroom_name, "Classroom name", false, "Multimedia Room 1");
	API_DTO_FIELD(UInt32, arrived_count, "Arrived count", true, 1);
	API_DTO_FIELD(UInt32, should_arrive_count, "Expected count", true, 1);
	API_DTO_FIELD(UInt32, evaluated_count, "Evaluated count", true, static_cast<v_uint32>(0));
	API_DTO_FIELD(Boolean, can_comment, "Can comment", true, true);
	API_DTO_FIELD(Boolean, can_sign, "Can sign", true, true);
};

class CommonDatetimeDTO : public oatpp::DTO
{
	DTO_INIT(CommonDatetimeDTO, DTO);

	API_DTO_FIELD(String, date, "Query date", true, "2026-03-15");
	API_DTO_FIELD(String, date_label, "Date label", true, "Today timetable");
	API_DTO_FIELD(UInt32, lesson_count, "Lesson count", true, 3);
	API_DTO_FIELD(List<CommonDatetimeLessonDTO::Wrapper>, lessons, "Lesson list", true, {});
};

#include OATPP_CODEGEN_END(DTO)

#endif
