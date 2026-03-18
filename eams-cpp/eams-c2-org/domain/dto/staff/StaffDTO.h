#pragma once

#ifndef _STAFFDTO_H_
#define _STAFFDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	员工数据传输对象
 */
class StaffDTO : public oatpp::DTO {
  DTO_INIT(StaffDTO, DTO);

};

#include OATPP_CODEGEN_END(DTO)
#endif // _STAFFDTO_H_
