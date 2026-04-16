#pragma once

#pragma once
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class StudentEnrollmentRecordsDTO : public oatpp::DTO
{
    DTO_INIT(StudentEnrollmentRecordsDTO, DTO);
	//学生ID
	API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("workbench.field.id"), true);
	//课程名称
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("workbench.field.name"), true);
	//报名时间
	API_DTO_FIELD_REQUIRE(String, enrollmentTime, ZH_WORDS_GETTER("workbench.field.time-enrollment"), true);
	//报名课程数
	API_DTO_FIELD_REQUIRE(UInt32, enrollmentCourseCount, ZH_WORDS_GETTER("workbench.field.course-enrollment"), true);
	//课程费
	API_DTO_FIELD_REQUIRE(Float64, courseFee, ZH_WORDS_GETTER("workbench.field.fee"), true);
};

class StudentEnrollmentRecordsPageDTO : public PageDTO<StudentEnrollmentRecordsDTO::Wrapper>
{
	DTO_INIT(StudentEnrollmentRecordsPageDTO, PageDTO<StudentEnrollmentRecordsDTO::Wrapper>);

};

#include OATPP_CODEGEN_END(DTO)
