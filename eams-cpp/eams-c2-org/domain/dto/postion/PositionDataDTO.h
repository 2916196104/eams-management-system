#pragma once

#ifndef _POSITIONDTODATA_H_
#define _POSITIONDTODATA_H_

#include "../../GlobalInclude.h"
#include "PermissionDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	职位数据权限数据传输对象
 */
class PositionDataDTO : public oatpp::DTO {
	DTO_INIT(PositionDataDTO, DTO);
	DTO_FIELD(Int32, id);               // 职位ID
	DTO_FIELD(String, name);             // 职位名称
	DTO_FIELD(Vector<oatpp::Object<PermissionDTO>>, permissions);  // 权限列表
};

#include OATPP_CODEGEN_END(DTO)
#endif // _POSITIONDTODATA_H_