#pragma once
#ifndef _SIGNVO_H_
#define _SIGNVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/SignAndRemark/SignDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)
/*
*	签到分页显示对象
*   封装分页签到记录的 JSON 响应
*	将 SignPageDTO 包装为 SignPageJsonVO（需要返回分页）
*/
class SignPageJsonVO : public JsonVO<SignPageDTO::Wrapper>
{
	DTO_INIT(SignPageJsonVO, JsonVO<SignPageDTO::Wrapper>);
};


/*
*	签到列表显示对象
*	封装签到记录列表的 JSON 响应
*	将 std::vector<SignDTO::Wrapper> 包装为 SignListJsonVO（需要返回签到记录列表（不分页））
*/
class SignListJsonVO : public ListJsonVO<SignDTO::Wrapper>
{
	DTO_INIT(SignListJsonVO, ListJsonVO<SignDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_SIGNVO_H_
