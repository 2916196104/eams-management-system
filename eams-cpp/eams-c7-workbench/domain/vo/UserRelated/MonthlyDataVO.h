#pragma once
#ifndef _MONTHLYDATAVO_H_
#define _MONTHLYDATAVO_H_
#include "../../GlobalInclude.h"
#include "domain/dto/UserRelated/MonthlyDataDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

///**
//*班级分页显示对象
//*/
//class MonthlyDataPageJsonVO : public JsonVO<MonthlyDataPageDTO::Wrapper>
//{
//	DTO_INIT(MonthlyDataPageJsonVO, JsonVO<MonthlyDataPageDTO::Wrapper>);
//};

/**
*班级列表显示对象
*/
class MonthlyDataListJsonVO : public ListJsonVO<MonthlyDataDTO::Wrapper>
{
	DTO_INIT(MonthlyDataListJsonVO, ListJsonVO<MonthlyDataDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif

