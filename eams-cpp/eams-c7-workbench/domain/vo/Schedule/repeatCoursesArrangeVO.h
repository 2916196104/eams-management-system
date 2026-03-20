#ifndef _REPEATCOURSESARRANGEVO_H_
#define _REPEATCOURSESARRANGEVO_H_

#include"../../GlobalInclude.h"
#include"../../dto/Schedule/repeatCoursesArrangeDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class repeatCoursesArrangeJsonVO :public JsonVO<repeatCoursesArrangeDTO::Wrapper>
{

	DTO_INIT(repeatCoursesArrangeJsonVO, JsonVO< repeatCoursesArrangeDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)
#endif