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
#ifndef _SCOREVO_H_
#define _SCOREVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/score/scoreDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 成绩分页显示对象
 */
class ScorePageJsonVO : public JsonVO<ScorePageDTO::Wrapper>
{
	DTO_INIT(ScorePageJsonVO, JsonVO<ScorePageDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_SCOREVO_H_