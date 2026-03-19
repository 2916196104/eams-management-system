
#pragma once
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class StudentCourseProgressDTO : public oatpp::DTO
{
    DTO_INIT(StudentCourseProgressDTO, DTO);
    //学生ID
    API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("workbench.field.id"), true);
    //课程名称
    API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("workbench.field.name"), true);
    //审核状态
    API_DTO_FIELD_REQUIRE(String, reviewstatus, ZH_WORDS_GETTER("workbench.field.status-review"), true);
    //总共课程数
    API_DTO_FIELD_REQUIRE(UInt32, totalCourseCount, ZH_WORDS_GETTER("workbench.field.total-course"), true);
    //已上课程数
    API_DTO_FIELD_REQUIRE(UInt32, completedCourseCount, ZH_WORDS_GETTER("workbench.field.completed-course"), true);
    //剩余课程数
    API_DTO_FIELD_REQUIRE(UInt32, remainingCourseCount, ZH_WORDS_GETTER("workbench.field.remaining-course"), true);
};

class StudentCourseProgressPageDTO : public PageDTO<StudentCourseProgressDTO::Wrapper>
{
    DTO_INIT(StudentCourseProgressPageDTO, PageDTO<StudentCourseProgressDTO::Wrapper>);

};

#include OATPP_CODEGEN_END(DTO)
