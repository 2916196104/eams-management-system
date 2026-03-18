/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/08 21:19:14

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
#include "stdafx.h"
#include "cardcontroller.h"
//实现接口执行函数

/*
* 获取试听卡列表
*/
cardListJsonVO::Wrapper cardController::executeCardListQuery() {
	return {};
}
/*
* 获取试听卡使用规则
*/
cardRuleJsonVO::Wrapper cardController::executeCardRuleQuery() {
	return {};
}

ListeningCardListJsonVO::Wrapper cardController::execQueryCardList(const oatpp::String& userName)
{
	return {};
}

StringJsonVO::Wrapper cardController::execModifyCard(const receiveCardDTO::Wrapper& dto, const PayloadDTO& payload)
{
	return{};
}