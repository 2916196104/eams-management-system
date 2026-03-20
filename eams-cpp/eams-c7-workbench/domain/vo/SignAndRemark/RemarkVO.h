#pragma once
#ifndef _REMARKVO_H_
#define _REMARKVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/SignAndRemark/RemarkDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)
/*
*	签到分页显示对象
*   封装分页签到记录的 JSON 响应
*	将 SignPageDTO 包装为 SignPageJsonVO（需要返回分页）
*/
class RemarkPageJsonVO : public JsonVO<RemarkPageDTO::Wrapper>
{
	DTO_INIT(RemarkPageJsonVO, JsonVO<RemarkPageDTO::Wrapper>);
};


/*
*	签到列表显示对象
*	封装签到记录列表的 JSON 响应
*	将 std::vector<SignDTO::Wrapper> 包装为 SignListJsonVO（需要返回签到记录列表（不分页））
*/
class RemarkListJsonVO : public ListJsonVO<RemarkDTO::Wrapper>
{
	DTO_INIT(RemarkListJsonVO, ListJsonVO<RemarkDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_SIGNVO_H_
