
#pragma once
#include "../../GlobalInclude.h"
#include "domain/dto/Student_Enrollment_Records/StudentEnrollmentRecordsDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class StudentEnrollmentRecordsPageJsonVO : public JsonVO<StudentEnrollmentRecordsPageDTO::Wrapper>
{
    DTO_INIT(StudentEnrollmentRecordsPageJsonVO, JsonVO<StudentEnrollmentRecordsPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

