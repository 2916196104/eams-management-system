
#pragma once
#include "../../GlobalInclude.h"
#include "domain/dto/Student_Class_Hour Records/ClassHourRecordsDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class StudentClassHourRecordsPageJsonVO : public JsonVO<StudentClassHourRecordsPageDTO::Wrapper>
{
    DTO_INIT(StudentClassHourRecordsPageJsonVO, JsonVO<StudentClassHourRecordsPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
