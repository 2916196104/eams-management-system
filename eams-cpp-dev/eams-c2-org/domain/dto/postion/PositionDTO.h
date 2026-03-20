#pragma once

#ifndef _POSITIONDTO_H_
#define _POSITIONDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	职位数据传输对象
 */
class PositionDTO : public oatpp::DTO {
  DTO_INIT(PositionDTO, DTO);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _POSITIONDTO_H_