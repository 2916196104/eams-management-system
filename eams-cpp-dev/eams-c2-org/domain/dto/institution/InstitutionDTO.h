#pragma once

#ifndef _INSTITUTIONDTO_H_
#define _INSTITUTIONDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	机构数据传输对象
 */
class InstitutionDTO : public oatpp::DTO {
  DTO_INIT(InstitutionDTO, DTO);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _INSTITUTIONDTO_H_
