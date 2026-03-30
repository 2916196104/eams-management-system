#pragma once 





#ifndef _LESSONCOMMENT_VO_
#define _LESSONCOMMENT_VO_
#include "../../../GlobalInclude.h"
#include "../../../dto/home/LessonComment/LessonCommentDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class LessonCommentPageJsonVO : public JsonVO<LessonCommentPageDTO::Wrapper>
{
	DTO_INIT(LessonCommentPageJsonVO, JsonVO<LessonCommentPageDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)
#endif