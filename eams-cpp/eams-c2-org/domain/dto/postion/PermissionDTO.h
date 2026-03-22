#pragma once
#include "../../GlobalInclude.h"   // 可能已经包含了必要的 oatpp 头文件
#include OATPP_CODEGEN_BEGIN(DTO)

class PermissionDTO : public oatpp::DTO {
    DTO_INIT(PermissionDTO, DTO)
        DTO_FIELD(Int32, id);
    DTO_FIELD(String, code);
    DTO_FIELD(String, name);
    // 其他字段...
};

#include OATPP_CODEGEN_END(DTO)