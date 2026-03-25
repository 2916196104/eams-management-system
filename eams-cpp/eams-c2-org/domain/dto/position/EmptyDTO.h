#pragma once
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class EmptyDTO : public oatpp::DTO {
    DTO_INIT(EmptyDTO, DTO)
        // 无字段，序列化后为 {}
};

#include OATPP_CODEGEN_END(DTO)