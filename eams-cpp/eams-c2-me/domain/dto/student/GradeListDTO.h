#pragma once


#include "../../GlobalInclude.h"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)
class GradeListDTO : public oatpp::DTO {
	DTO_INIT(GradeListDTO, DTO)
	DTO_FIELD(List<Object<GradeDTO>>, list);
};



#include OATPP_CODEGEN_END(DTO)