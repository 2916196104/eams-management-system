#pragma once

#include "../../GlobalInclude.h"


#include OATPP_CODEGEN_BEGIN(DTO)



/**
 * 定义一个完整用户信息的数据传输模型
 */
class GradeDTO : public oatpp::DTO {
    DTO_INIT(GradeDTO, DTO);
    API_DTO_FIELD(String, name, ZH_WORDS_GETTER("student.grade"), true, "");

};
class GradePageDTO : public PageDTO<GradeDTO::Wrapper>
{
    DTO_INIT(GradePageDTO, PageDTO<GradeDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)