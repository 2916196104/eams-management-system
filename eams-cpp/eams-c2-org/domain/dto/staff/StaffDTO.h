#pragma once

#ifndef _STAFFDTO_H_
#define _STAFFDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	鍛樺伐鏁版嵁浼犺緭瀵硅薄
 */
class StaffDTO : public oatpp::DTO {
  DTO_INIT(StaffDTO, DTO);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _STAFFDTO_H_
