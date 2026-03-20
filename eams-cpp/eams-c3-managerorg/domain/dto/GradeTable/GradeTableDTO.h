#ifndef __GRADE_TABLE_DTO_H__
#define __GRADE_TABLE_DTO_H__

#include "domain/GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*�ɼ���DTO��*/


class GradeTableDTO : public oatpp::DTO
{
	DTO_INIT(GradeTableDTO, DTO);
};

#include OATPP_CODEGEN_END(DTO)

#endif