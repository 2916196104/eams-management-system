#pragma once

#include "../../../GlobalInclude.h"
#include "domain/dto/Homework/homeworklist/HomeworkListDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class HomeworkListJsonVO :public JsonVO<HomeworkListDTO::Wrapper>
{
	DTO_INIT(HomeworkListJsonVO, JsonVO<HomeworkListDTO::Wrapper>);
};

class HomeworkListPageJsonVO :public JsonVO<HomeworkListPageDTO::Wrapper>
{
	DTO_INIT(HomeworkListPageJsonVO, JsonVO<HomeworkListPageDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)