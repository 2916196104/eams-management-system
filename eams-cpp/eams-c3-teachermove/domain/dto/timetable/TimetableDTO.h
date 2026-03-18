#ifndef __TIMETABLE_DTO_H__
#define __TIMETABLE_DTO_H__

#include "domain/vo/BaseJsonVO.h"
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/* Timetable-related business DTO classes */
class TimetableDTO : public oatpp::DTO
{
	DTO_INIT(TimetableDTO, DTO)
};

// --- 1. Student list (with conditions + pagination) - response list item DTO ---
class TimetableStudentDTO : public oatpp::DTO {
	DTO_INIT(TimetableStudentDTO, DTO)

		API_DTO_FIELD(String, id, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.studentID"), true, "10001")
		API_DTO_FIELD(String, name, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.studentName"), true, "111")
		API_DTO_FIELD(String, phone, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.phone"), false, "15865842975")
		API_DTO_FIELD(String, gender, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.gender"), false, "1")
		API_DTO_FIELD(Int32, rest_hour, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.restHour"), false, 108)
};

// Since the framework does not have a built-in PageJsonVO, we need to define a custom pagination VO for the current student list.
class TimetableStudentPageJsonVO : public JsonVO<PageDTO<TimetableStudentDTO::Wrapper>::Wrapper> {
	DTO_INIT(TimetableStudentPageJsonVO, JsonVO<PageDTO<TimetableStudentDTO::Wrapper>::Wrapper>)
};

// --- 2. Add student to lesson - request parameter DTO ---
class AddStudentToLessonDTO : public oatpp::DTO {
	DTO_INIT(AddStudentToLessonDTO, DTO)

		API_DTO_FIELD(String, course_id, ZH_WORDS_GETTER("timetable.dto.AddStudentToLessonDTO.courseId"), true, "c_001")
		API_DTO_FIELD_REQUIRE(List<String>, studentIds, ZH_WORDS_GETTER("timetable.dto.AddStudentToLessonDTO.studentIds"), true)
};

// --- 3. Get student course list - response list item DTO ---
class TimetableStudentCourseDTO : public oatpp::DTO {
	DTO_INIT(TimetableStudentCourseDTO, DTO)

		API_DTO_FIELD(String, course_id, ZH_WORDS_GETTER("timetable.dto.AddStudentToLessonDTO.courseId"), true, "c_001")
		API_DTO_FIELD(Int32, rest_hour, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.restHour"), true, 0)
		API_DTO_FIELD(String, title, ZH_WORDS_GETTER("timetable.dto.TimetableStudentCourseDTO.courseTitle"), true, "CollegePhysics")
		API_DTO_FIELD(String, teacher_id, ZH_WORDS_GETTER("timetable.dto.TimetableStudentCourseDTO.teacherId"), false, "TeacherWang")
		API_DTO_FIELD(String, sn, ZH_WORDS_GETTER("timetable.dto.TimetableStudentCourseDTO.sn"), false, "2")
};

#include OATPP_CODEGEN_END(DTO)

#endif