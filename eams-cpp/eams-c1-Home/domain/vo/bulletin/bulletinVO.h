#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/14 19:27:22

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
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