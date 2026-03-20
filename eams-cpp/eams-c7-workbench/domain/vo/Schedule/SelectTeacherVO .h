#pragma once
#ifndef _SELECTTEACHERVO_H_
#define _SELECTTEACHERVO_H_
#include "../../GlobalInclude.h"
#include "../../dto/schedule/SelectTeacherDTO .h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
*班级分页显示对象
*/
class SelectTeacherPageJsonVO : public JsonVO<SelectTeacherPageDTO::Wrapper>
{
	DTO_INIT(SelectTeacherPageJsonVO, JsonVO<SelectTeacherPageDTO::Wrapper>);
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

