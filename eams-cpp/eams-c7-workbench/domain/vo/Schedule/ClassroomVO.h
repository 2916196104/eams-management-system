#ifndef _CLASSROOMVO_H_
#define _CLASSROOMVO_H_

#include"../../GlobalInclude.h"
#include"../../dto/Schedule/ClassroomDTO.h"
//#include"lib-oatpp/domain/JsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClassroomPageJsonVO :public JsonVO<ClassroomPageDTO::Wrapper>
{

	DTO_INIT(ClassroomPageJsonVO,JsonVO<ClassroomPageDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)
#endif