#pragma once

#ifndef _STUDENTDTO_H_
#define _STUDENTDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	瀛︾敓鏁版嵁浼犺緭瀵硅薄
 */
class StudentDTO : public oatpp::DTO {
  DTO_INIT(StudentDTO, DTO);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _STUDENTDTO_H_
