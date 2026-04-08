#pragma once
#ifndef _STUDENTVO_H_
#define _STUDENTVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/student/StudentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 单个学员返回VO
 */
class StudentJsonVO : public JsonVO<StudentDTO::Wrapper> {
    DTO_INIT(StudentJsonVO, JsonVO<StudentDTO::Wrapper>);
};

/**
 * 学员分页列表返回VO
 */
class StudentPageJsonVO : public JsonVO<StudentPageDTO::Wrapper> {
    DTO_INIT(StudentPageJsonVO, JsonVO<StudentPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif