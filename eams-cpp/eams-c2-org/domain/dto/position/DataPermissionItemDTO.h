#pragma once
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class DataPermissionItemDTO : public oatpp::DTO {
    DTO_INIT(DataPermissionItemDTO, DTO)
        DTO_FIELD(String, dataTableName);       // 数据表名称
    DTO_FIELD(String, dataScopeType);        // 数据范围类型
    DTO_FIELD(String, dataTableCode);        // 数据表code
    DTO_FIELD(String, dataOwnerField);       // 数据负责人字段
    DTO_FIELD(String, dataOrgField);         // 数据所属组织字段
    // 如果需要操作，可以加一个 id 字段
    DTO_FIELD(Int32, id);                     // 权限项ID（用于编辑/删除）
};

#include OATPP_CODEGEN_END(DTO)