#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/08 21:10:30

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
#ifndef _CARDCONTRULLER_H_
#define _CARDCONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/vo/listening-card/cardVO.h"
#include "domain/query/listening-card/cardquery.h"
#include"../../service/ListeningCardListService.h"


#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("listening-card.tag")

//试听卡模块控制器
class cardController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(cardController);
	//
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("listening-card.queryCardSummary"), queryMyCardList, ListeningCardListJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "userId", ZH_WORDS_GETTER("listening-card.userID"), "", true);
	);
	//
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/app/sCenter/course/myTrialList", queryMyCardList, QUERY(String,userId), execQueryMyCardList(userId));

	// 定义获取试听卡接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("listening-card.get.list"), cardQuery,cardListJsonVO::Wrapper, API_TAG);
	// 定义获取试听卡接口端点
	API_HANDLER_ENDPOINT_NOPARAM_AUTH(API_M_GET, "/app/sCenter/course/trialList", cardQuery, executeCardListQuery());

	// 3.1 定义修改试听卡状态接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("listening-card.receive"), receiveCard, StringJsonVO::Wrapper, API_TAG);
	// 3.2 定义修改试听卡状态接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/app/sCenter/course/catchTrial/{trialId}", receiveCard, BODY_DTO(receiveCardDTO::Wrapper, dto), execReceiveCard(dto, authObject->getPayload()));

	// 定义获取试听卡规则接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("listening-card.get.rule"), cardRuleQuery, cardRuleJsonVO::Wrapper, API_TAG);
	// 定义获取试听卡规则接口端点
	API_HANDLER_ENDPOINT_NOPARAM_AUTH(API_M_GET, "/app/sCenter/course/getRule", cardRuleQuery, executeCardRuleQuery());


	
private:
	//查询我的试听卡
	ListeningCardPageJsonVO::Wrapper execQueryMyCardList(const oatpp::String& userId);
	//领取试听卡
	StringJsonVO::Wrapper execReceiveCard(const receiveCardDTO::Wrapper& dto, const PayloadDTO& payload);
	cardListJsonVO::Wrapper executeCardListQuery();
	cardRuleJsonVO::Wrapper executeCardRuleQuery();
};


#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_CARDCONTROLLER_H_