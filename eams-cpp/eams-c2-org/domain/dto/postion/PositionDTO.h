#pragma once

#ifndef _POSITIONDTO_H_
#define _POSITIONDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	鑱屼綅鏁版嵁浼犺緭瀵硅薄
 */
class PositionDTO : public oatpp::DTO {
  DTO_INIT(PositionDTO, DTO);
  DTO_FIELD(Int32, id);               // 鑱屼綅ID
  DTO_FIELD(String, name);             // 鑱屼綅鍚嶇О
  DTO_FIELD(String, description);      // 鑱屼綅鎻忚堪
};

#include OATPP_CODEGEN_END(DTO)
#endif // _POSITIONDTO_H_