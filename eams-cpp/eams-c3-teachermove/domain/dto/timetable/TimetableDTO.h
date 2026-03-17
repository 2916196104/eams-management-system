#ifndef __TIMETABLE_DTO_H__
#define __TIMETABLE_DTO_H__

#include "domain/vo/BaseJsonVO.h"
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/* 课表相关业务DTO类*/
class TimetableDTO: public oatpp::DTO
{
	DTO_INIT(TimetableDTO, DTO)
};

// --- 1. 获取学员列表(条件+分页) - 响应的列表项 DTO ---
class TimetableStudentDTO : public oatpp::DTO {
	DTO_INIT(TimetableStudentDTO, DTO)

	API_DTO_FIELD(String, id, "学员ID", true, "10001")
	API_DTO_FIELD(String, name, "学员姓名", true, "张三")
	API_DTO_FIELD(String, head_img, "头像地址", false, "https://example.com/head.png")
	API_DTO_FIELD(String, gender, "性别1男2女", false, "1")
};

//由于框架没有自带 PageJsonVO，需要自定义一个属于当前学员列表的分页 VO
class TimetableStudentPageJsonVO : public JsonVO<PageDTO<TimetableStudentDTO::Wrapper>::Wrapper> {
	DTO_INIT(TimetableStudentPageJsonVO, JsonVO<PageDTO<TimetableStudentDTO::Wrapper>::Wrapper>)
};

// --- 2. 添加学员到课次 - 请求入参 DTO ---
class AddStudentToLessonDTO : public oatpp::DTO {
	DTO_INIT(AddStudentToLessonDTO, DTO)

	API_DTO_FIELD(String, course_id, "课程ID", true, "c_001")
	API_DTO_FIELD_REQUIRE(List<String>, studentIds, "要添加的学员ID列表", true)
};

// --- 3. 获取学员课程列表 - 响应的列表项 DTO ---
class TimetableStudentCourseDTO : public oatpp::DTO {
	DTO_INIT(TimetableStudentCourseDTO, DTO)

	API_DTO_FIELD(String, course_id, "课程ID", true, "c_001")
	API_DTO_FIELD(String, title, "课程标题", true, "大学物理")
	API_DTO_FIELD(String, teacher_id, "主讲人", false, "王老师")
	API_DTO_FIELD(String, sn, "课节数", false, "2")
};

#include OATPP_CODEGEN_END(DTO)

#endif