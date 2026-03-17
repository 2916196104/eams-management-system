#pragma once

#ifndef _POSITIONDTODATA_H_
#define _POSITIONDTODATA_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	职位数据权限数据传输对象
 */
class PositionDataDTO : public oatpp::DTO {
  DTO_INIT(PositionDataDTO, DTO);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _POSITIONDTODATA_H_
