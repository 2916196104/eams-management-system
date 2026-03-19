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




/**
 * 示例分页显示JsonVO，用于响应给客户端的Json对象
 */
class QueryFollowUprecordsJsonVO : public JsonVO<QuereyFollowUprecordsDTO::Wrapper> {
    DTO_INIT(QueryFollowUprecordsJsonVO, JsonVO<QuereyFollowUprecordsDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif