#ifndef __CLASS_DTO_H__
#define __CLASS_DTO_H__

#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*¿Î³ÌDTOÀà*/


class ClassDTO : public oatpp::DTO
{
	DTO_INIT(ClassDTO, DTO)
};

#include OATPP_CODEGEN_END(DTO)

#endif