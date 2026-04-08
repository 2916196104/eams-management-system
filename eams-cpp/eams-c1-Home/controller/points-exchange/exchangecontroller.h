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
#ifndef _EXCHANGECONTRULLER_H_
#define _EXCHANGECONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/vo/points-exchange/exchangeVO.h"
#include "domain/query/points-exchange/exchangequery.h"
#include"service/points-exchange/points-ExchangeService.h"


#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("exchange.tag")

//积分兑换模块控制器
class exchangeController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(exchangeController);
public: // 定义接口

	// 1. 定义查询所有积分礼品列表信息（条件+分页）接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("exchange.query-allGoods.summary"), queryAllGoods, PageQuery, GoodsPageJsonVO::Wrapper, API_TAG);
	// 1.2 定义查询所有积分礼品列表信息（条件+分页）接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/app/sCenter/credit/list", queryAllGoods, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, PageQuery, queryParams); API_HANDLER_RESP_VO(executeQueryAll(query)););

	// 2. 定义获取积分礼品详情接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("exchange.get-goods-detail.summary"), getGoodsDetail, GoodsDetailJsonVO::Wrapper, API_TAG);
	// 2.2 定义获取积分礼品详情接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/app/sCenter/credit/info", getGoodsDetail, QUERY(UInt64, id), executeGetGoodsDetail(id));

	// 3. 定义查询当前用户兑换记录（条件+分页）接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("exchange.query-accept.summary"), queryAcceptGoods, AcceptGoodsQuery, AcceptGoodsPageJsonVO::Wrapper, API_TAG);
	// 3.2 定义查询当前用户兑换记录（条件+分页）接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/app/sCenter/credit/exchangeRecord", queryAcceptGoods, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, AcceptGoodsQuery, queryParams); API_HANDLER_RESP_VO(executeQueryAcceptGoods(query)););

	// 4. 定义查询积分兑换规则（通过Id值来查询，也可查询数据库中其他规则）接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("exchange.query-rule.summary"), queryRule, SettingJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(UInt64, "id", ZH_WORDS_GETTER("goods.setting.id"), 107, true);
	);
	// 4.2 定义查询积分兑换规则（通过Id值来查询，也可查询数据库中其他规则）接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/app/sCenter/credit/getRule", queryRule, QUERY(UInt64, id), executeQueryRule(id));

	// 5. 定义兑换礼品接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("exchange.submit-exchange.summary"), submitExchange, ExchangeResultJsonVO::Wrapper, API_TAG,

		);

	// 5.2 定义兑换礼品接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/app/sCenter/credit/exchange", submitExchange,
		BODY_DTO(ExchangeSubmitDTO::Wrapper, request),
		executeSubmitExchange(request, authObject->getPayload())
	);

private: // 定义接口执行函数
	GoodsPageJsonVO::Wrapper executeQueryAll(const PageQuery::Wrapper& query);
	GoodsDetailJsonVO::Wrapper executeGetGoodsDetail(const UInt64& id);
	AcceptGoodsPageJsonVO::Wrapper executeQueryAcceptGoods(const AcceptGoodsQuery::Wrapper& acceptGoods);
	SettingJsonVO::Wrapper executeQueryRule(const UInt64& id);
	ExchangeResultJsonVO::Wrapper executeSubmitExchange(const ExchangeSubmitDTO::Wrapper& request, const PayloadDTO& payload);

};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_EXCHANGECONTROLLER_H_