#pragma once
#ifndef _SELECTCLASSVO_H_
#define _SELECTCLASSVO_H_
#include "../../GlobalInclude.h"
#include "../../dto/schedule/SelectClassDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
*班级分页显示对象
*/
class SelectClassPageJsonVO : public JsonVO<SelectClassPageDTO::Wrapper>
{
	DTO_INIT(SelectClassPageJsonVO, JsonVO<SelectClassPageDTO::Wrapper>);
};

///**
//*班级列表显示对象
//*/
//class SelectClassListJsonVO : public ListJsonVO<SelectClassDTO::Wrapper>
//{
//	DTO_INIT(SelectClassListJsonVO, ListJsonVO<SelectClassDTO::Wrapper>);
//};

#include OATPP_CODEGEN_END(DTO)

#endif

