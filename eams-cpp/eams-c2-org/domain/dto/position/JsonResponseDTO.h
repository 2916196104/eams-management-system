#pragma once
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class JsonResponseDTO : public oatpp::DTO {
    DTO_INIT(JsonResponseDTO, DTO)
        DTO_FIELD(Int32, errCode);
    DTO_FIELD(String, msg);
    DTO_FIELD(T, data);
};

#include OATPP_CODEGEN_END(DTO)