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
#include "service/listening-card/CardService.h"
//实现接口执行函数

/*
* 获取试听卡列表
*/
cardListJsonVO::Wrapper cardController::executeCardListQuery() {
	// 查询试听卡数据
	auto result = CardService().getAvailableCardList();
	// 构建返回结果
	auto jvo = cardListJsonVO::createShared();
	jvo->success(result);
	return jvo;
}
/*
* 获取试听卡使用规则
*/
cardRuleJsonVO::Wrapper cardController::executeCardRuleQuery() {
	// 查询试听卡规则数据
	auto result = CardService().getCardUsageRules();
	// 构建返回结果
	auto jvo = cardRuleJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

ListeningCardPageJsonVO::Wrapper cardController::execQueryMyCardList(const oatpp::String& userId)
{
	// 查询数据
	auto result = ListeningCardListService().listAll(userId);
	// 响应结果
	auto jvo = ListeningCardPageJsonVO::createShared();
	jvo->success(result);

	return jvo;
}

StringJsonVO::Wrapper cardController::execReceiveCard(const receiveCardDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();
	// 参数校验
	if ((!dto->trialId) || (!dto->userId))
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 执行数据修改
	dto->setPayload(&payload);
	if (ListeningCardListService().claimCard(dto)) {
		jvo->success("OK");
	}
	else
	{
		jvo->fail("ERROR");
	}
	// 响应结果
	return jvo;
}