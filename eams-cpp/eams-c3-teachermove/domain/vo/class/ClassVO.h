#ifndef __CLASS_VO_H__
#define __CLASS_VO_H__

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)



class ClassVO : public oatpp::DTO
{
	DTO_INIT(ClassVO, DTO)
};

#include OATPP_CODEGEN_END(DTO)

#endif