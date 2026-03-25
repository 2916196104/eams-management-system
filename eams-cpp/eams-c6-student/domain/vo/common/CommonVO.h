#pragma once
#ifndef __COMMON_VO_H__
#define __COMMON_VO_H__ 
#include"../../GlobalInclude.h"
#include"../../dto/common/CommonDTO.h"
#include "oatpp/core/macro/codegen.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)
class StudentJsonVO:public JsonVO<StudentDTO::Wrapper>
{
public:
    DTO_INIT(StudentJsonVO, JsonVO<StudentDTO::Wrapper>)
};
class RegistrationPageJsonVO:public JsonVO<RegistrationPageDTO::Wrapper>
{
public:
    DTO_INIT(RegistrationPageJsonVO, JsonVO<RegistrationPageDTO::Wrapper>)
};
class FileJsonVO:public JsonVO<FileOnlyDTO::Wrapper>
{
public:
    DTO_INIT(FileJsonVO, JsonVO<FileOnlyDTO::Wrapper>)
};
class PayFeesJsonVO :public JsonVO<PayFeesDTO::Wrapper> {
    DTO_INIT(PayFeesJsonVO,JsonVO<PayFeesDTO::Wrapper>)
};
class RefundJsonVO :public JsonVO<RefundDTO::Wrapper> {
    DTO_INIT(RefundJsonVO, JsonVO<RefundDTO::Wrapper>)
};
#include OATPP_CODEGEN_END(DTO)
#endif