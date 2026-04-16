
#pragma once
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class StudentClassHourRecordsDTO : public oatpp::DTO
{
    DTO_INIT(StudentClassHourRecordsDTO, DTO);
    //学生ID
    API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("workbench.field.id"), true);
    //课程名称
    API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("workbench.field.name"), true);
    //上课状态
	API_DTO_FIELD_REQUIRE(String, status, ZH_WORDS_GETTER("workbench.field.status-class"), true);
	//剩余课时数
	API_DTO_FIELD_REQUIRE(UInt32, remainingClassHourCount, ZH_WORDS_GETTER("workbench.field.remaining-hour"), true);

};

class StudentClassHourRecordsPageDTO : public PageDTO<StudentClassHourRecordsDTO::Wrapper>
{
    DTO_INIT(StudentClassHourRecordsPageDTO, PageDTO<StudentClassHourRecordsDTO::Wrapper>);

};

#include OATPP_CODEGEN_END(DTO)
