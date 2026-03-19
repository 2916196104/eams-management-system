
#pragma once
#include "../../GlobalInclude.h"
#include "domain/dto/Student_Course_Progress/StudentCourseProgressDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class StudentCourseProgressPageJsonVO : public JsonVO<StudentCourseProgressPageDTO::Wrapper>
{
    DTO_INIT(StudentCourseProgressPageJsonVO, JsonVO<StudentCourseProgressPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

