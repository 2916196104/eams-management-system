#pragma once

#ifndef _POSITIONDTODATA_H_
#define _POSITIONDTODATA_H_

#include "../../GlobalInclude.h"
#include "PermissionDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	鑱屼綅鏁版嵁鏉冮檺鏁版嵁浼犺緭瀵硅薄
 */
class PositionDataDTO : public oatpp::DTO {
  DTO_INIT(PositionDataDTO, DTO);
  DTO_FIELD(Int32, id);               // 鑱屼綅ID
  DTO_FIELD(String, name);             // 鑱屼綅鍚嶇О
  DTO_FIELD(Vector<oatpp::Object<PermissionDTO>>, permissions);  // 鏉冮檺鍒楄〃
};

#include OATPP_CODEGEN_END(DTO)
#endif // _POSITIONDTODATA_H_
