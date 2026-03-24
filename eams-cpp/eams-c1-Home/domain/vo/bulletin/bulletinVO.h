#pragma once
#ifndef _BULLETINVO_H_
#define _BULLETINVO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/bulletin/bulletinDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义显示对象
 */

//通知公告对象
class titleJsonVO : public JsonVO<titleDTO::Wrapper>
{
	DTO_INIT(titleJsonVO, JsonVO<titleDTO::Wrapper>);
};


class listPageJsonVO : public JsonVO<listPageDTO::Wrapper>
{
	DTO_INIT(listPageJsonVO, JsonVO<listPageDTO::Wrapper>);
};


class redJsonVO : public JsonVO<redDTO::Wrapper>
{
    DTO_INIT(redJsonVO, JsonVO<redDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_BULLETINKVO_H_