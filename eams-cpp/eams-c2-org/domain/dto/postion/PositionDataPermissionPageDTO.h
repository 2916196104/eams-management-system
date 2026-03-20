#pragma once
#include "../../GlobalInclude.h"
#include "PositionDataDTO.h"
#include "DataPermissionItemDTO.h" 
#include "domain/dto/postion/PositionDataPermissionQueryDTO.h"
#include "domain/dto/postion/PositionDataPermissionPageDTO.h"
#include "domain/vo/BaseJsonVO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class PositionDataPermissionPageDTO : public oatpp::DTO {
	DTO_INIT(PositionDataPermissionPageDTO, DTO);
	DTO_FIELD(Int64, total);                                    // ×Ü¼ÇÂ¼Êý
	DTO_FIELD(Vector<oatpp::Object<DataPermissionItemDTO>>, list);
};

#include OATPP_CODEGEN_END(DTO)