#pragma once
#ifndef CLASSDETAIL_DTO_
#define CLASSDETAIL_DTO_

#include"../../GlobalInclude.h"	
#include OATPP_CODEGEN_BEGIN(DTO)

/*
*班级数据传输对象
*/
class ClassDTO : public oatpp::DTO
{
	DTO_INIT(ClassDTO, DTO);
	API_DTO_FIELD_REQUIRE(String,id,ZH_WORDS_GETTER("class1.detail.ID"),true);
	API_DTO_FIELD_DEFAULT(String, class_name, ZH_WORDS_GETTER("class1.detail.ClassName"));
	API_DTO_FIELD_DEFAULT(String, staff_name, ZH_WORDS_GETTER("class1.detail.StaffName"));
	API_DTO_FIELD_DEFAULT(String, room_name, ZH_WORDS_GETTER("class1.detail.RoomName"));
	API_DTO_FIELD_DEFAULT(String, course_name, ZH_WORDS_GETTER("class1.detail.CourseName"));
	API_DTO_FIELD_DEFAULT(String, start_date, ZH_WORDS_GETTER("class1.detail.StartDate"));
	API_DTO_FIELD_DEFAULT(String, end_date, ZH_WORDS_GETTER("class1.detail.EndDate"));
	API_DTO_FIELD_DEFAULT(UInt64,course_lessons, ZH_WORDS_GETTER("class1.detail.CourseLessons"));
	API_DTO_FIELD_DEFAULT(UInt64, planed_student_count, ZH_WORDS_GETTER("class1.detail.PlanedStudentCount"));
	API_DTO_FIELD_DEFAULT(String,remark, ZH_WORDS_GETTER("class1.detail.Remark"));
	API_DTO_FIELD_DEFAULT(Int64, be_over, ZH_WORDS_GETTER("class1.detail.BeOver"));
};

class ClassDetailDTO : public ClassDTO
{
	DTO_INIT(ClassDetailDTO, ClassDTO);

};


#include OATPP_CODEGEN_END(DTO)
#endif // !CLASSCONTROLLER_DTO_
