#ifndef _FREECOURSESARRANGEVO_H_
#define _FREECOURSESARRANGEVO_H_

#include"../../GlobalInclude.h"
#include"../../dto/Schedule/freeCoursesArrangeDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class freeCoursesArrangeJsonVO :public JsonVO<freeCoursesArrangeDTO::Wrapper>
{
	DTO_INIT(freeCoursesArrangeJsonVO, JsonVO<freeCoursesArrangeDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)
#endif