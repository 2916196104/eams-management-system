#pragma once
#include "../../GlobalInclude.h"
#include "PositionDataDTO.h"
#include "DataPermissionItemDTO.h" 
#include "domain/dto/position/PositionDataPermissionQueryDTO.h"
#include "domain/dto/position/PositionDataPermissionPageDTO.h"
#include "domain/vo/BaseJsonVO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class PositionDataPermissionPageDTO : public oatpp::DTO {
	DTO_INIT(PositionDataPermissionPageDTO, DTO);
	DTO_FIELD(Int64, total);                                    // 总记录数
	DTO_FIELD(Vector<oatpp::Object<DataPermissionItemDTO>>, list);
};

#include OATPP_CODEGEN_END(DTO)