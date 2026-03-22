#pragma once
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class PositionDataPermissionQueryDTO : public oatpp::DTO {
	DTO_INIT(PositionDataPermissionQueryDTO, DTO);
        DTO_FIELD(Int32, positionId) = 1;    // 单个职位ID
    DTO_FIELD(Int32, page) = 1;
    DTO_FIELD(Int32, size) = 30;          // 默认30条/页

    DTO_FIELD_INFO(positionId) {
        info->description = "职位ID";
        info->required = true;
    }
    DTO_FIELD_INFO(page) {
        info->description = "当前页码，从1开始";
    }
    DTO_FIELD_INFO(size) {
        info->description = "每页记录数";
    }
};

#include OATPP_CODEGEN_END(DTO)