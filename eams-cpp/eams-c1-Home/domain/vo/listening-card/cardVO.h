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
#ifndef _CARDVO_H_
#define _CARDVO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/listening-card/cardDTO.h"
#include "../lib-oatpp/include/domain/vo/BaseJsonVO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

///**
// * 定义显示对象
// */
//class cardJsonVO : public JsonVO<cardDTO::Wrapper> {
//	DTO_INIT(cardJsonVO, JsonVO<cardDTO::Wrapper>);
//};

/**
 * 试听卡规则显示对象
 */
class cardRuleJsonVO : public JsonVO<cardRuleDTO::Wrapper> {
	DTO_INIT(cardRuleJsonVO, JsonVO<cardRuleDTO::Wrapper>);
};
/**
 * 定义列表显示对象
 */
class cardListJsonVO : public ListJsonVO<cardDTO::Wrapper> {
	DTO_INIT(cardListJsonVO, ListJsonVO<cardDTO::Wrapper>);
};
/**
 * 定义显示对象
 * 试听卡分页显示对象
 */


class ListeningCardPageJsonVO :public JsonVO< ListeningCardPageDTO::Wrapper>
{
	DTO_INIT(ListeningCardPageJsonVO, JsonVO< ListeningCardPageDTO::Wrapper>);
};

/**
 * 试听卡列表显示对象
 */
class ListeningCardListJsonVO :public ListJsonVO< ListeningCardDTO::Wrapper>
{
	DTO_INIT(ListeningCardListJsonVO, ListJsonVO< ListeningCardDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)

#endif // !_CARDVO_H_