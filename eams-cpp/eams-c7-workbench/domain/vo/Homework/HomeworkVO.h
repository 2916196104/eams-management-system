#pragma once
#ifndef _HOMEWORKVO_H_
#define _HOMEWORKVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/homework/HomeworkDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
*	作业分页显示对象
*   封装分页作业记录的 JSON 响应
*/
class HomeworkPageJsonVO : public JsonVO<HomeworkPageDTO::Wrapper>
{
	DTO_INIT(HomeworkPageJsonVO, JsonVO<HomeworkPageDTO::Wrapper>);
};


/*
*	作业列表显示对象
*	封装作业记录列表的 JSON 响应
*/
class HomeworkListJsonVO : public ListJsonVO<HomeworkDTO::Wrapper>
{
	DTO_INIT(HomeworkListJsonVO, ListJsonVO<HomeworkDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_HOMEWORKVO_H_
