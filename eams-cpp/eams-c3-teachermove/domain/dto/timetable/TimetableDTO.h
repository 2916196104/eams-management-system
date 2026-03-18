#ifndef __TIMETABLE_DTO_H__
#define __TIMETABLE_DTO_H__

#include "domain/vo/BaseJsonVO.h"
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/* 课表相关业务DTO类 */
class TimetableDTO: public oatpp::DTO
{
	DTO_INIT(TimetableDTO, DTO)
};

// --- 1. 获取学员列表(条件+分页) - 响应的列表项 DTO ---
class TimetableStudentDTO : public oatpp::DTO {
	DTO_INIT(TimetableStudentDTO, DTO)

	API_DTO_FIELD(String, id, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.studentID"),true, "10001")
	API_DTO_FIELD(String, name, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.studentName"), true, "张三")
	API_DTO_FIELD(String, phone, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.phone"), false, "15865842975")
	API_DTO_FIELD(String, gender, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.gender"), false, "1")
	API_DTO_FIELD(Int32, rest_hour, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.restHour"), false, 108)
};

// 由于框架没有自带 PageJsonVO，需要自定义一个属于当前学员列表的分页 VO
class TimetableStudentPageJsonVO : public JsonVO<PageDTO<TimetableStudentDTO::Wrapper>::Wrapper> {
	DTO_INIT(TimetableStudentPageJsonVO, JsonVO<PageDTO<TimetableStudentDTO::Wrapper>::Wrapper>)
};

// --- 2. 添加学员到课次 - 请求入参 DTO ---
class AddStudentToLessonDTO : public oatpp::DTO {
	DTO_INIT(AddStudentToLessonDTO, DTO)

	API_DTO_FIELD(String, course_id, ZH_WORDS_GETTER("timetable.dto.AddStudentToLessonDTO.courseId"), true, "c_001")
	API_DTO_FIELD_REQUIRE(List<String>, studentIds, ZH_WORDS_GETTER("timetable.dto.AddStudentToLessonDTO.studentIds"), true)
};

// --- 3. 获取学员课程列表 - 响应的列表项 DTO ---
class TimetableStudentCourseDTO : public oatpp::DTO {
	DTO_INIT(TimetableStudentCourseDTO, DTO)

	API_DTO_FIELD(String, course_id, ZH_WORDS_GETTER("timetable.dto.AddStudentToLessonDTO.courseId"), true, "c_001")
	API_DTO_FIELD(Int32, rest_hour, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.restHour"), true, 0)
	API_DTO_FIELD(String, title, ZH_WORDS_GETTER("timetable.dto.TimetableStudentCourseDTO.courseTitle"), true, "大学物理")
	API_DTO_FIELD(String, teacher_id, ZH_WORDS_GETTER("timetable.dto.TimetableStudentCourseDTO.teacherId"), false, "王老师")
	API_DTO_FIELD(String, sn, ZH_WORDS_GETTER("timetable.dto.TimetableStudentCourseDTO.sn"), false, "2")
};

#include OATPP_CODEGEN_END(DTO)

#endif