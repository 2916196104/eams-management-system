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
#include "exchangecontroller.h"
#include "service/points-exchange/exchangeService.h"

//实现接口执行函数


// 定义查询所有积分礼品列表信息
GoodsPageJsonVO::Wrapper exchangeController::executeQueryAll(const PageQuery::Wrapper& query)
{
	exchangeService es;
	auto vo = GoodsPageJsonVO::createShared();
	vo->success(es.listAllGoods(query));
	return vo;
}

// 定义查询当前用户兑换记录
AcceptGoodsPageJsonVO::Wrapper exchangeController::executeQueryAcceptGoods(const AcceptGoodsQuery::Wrapper& query)
{
	exchangeService es;
	auto vo = AcceptGoodsPageJsonVO::createShared();
	vo->success(es.listAcceptGoods(query));
	return vo;
}

//定义查询积分兑换规则
SettingJsonVO::Wrapper exchangeController::executeQueryRule(const UInt64& id)
{
	exchangeService es;
	auto vo = SettingJsonVO::createShared();
	vo->success(es.getSetting(id));
	return vo;
}


/*
查询积分兑换记录详情
*/
GoodsDetailJsonVO::Wrapper exchangeController::executeGetGoodsDetail(const UInt64& id)
{

    try
    {
        ExchangeService service;
        auto data = service.getGoodsDetail(id);

        auto result = GoodsDetailJsonVO::createShared();
        result->success(data);
        return result;
    }
    catch (const std::invalid_argument& e)
    {
        // 参数错误 - 传入空数据
        auto result = GoodsDetailJsonVO::createShared();
        GoodsDetailDTO::Wrapper emptyData = GoodsDetailDTO::createShared();
        result->fail(emptyData);
        // 如果需要自定义错误消息，可以手动设置
        result->code = 400;
        result->message = e.what();
        return result;
    }
    catch (const std::runtime_error& e)
    {
        // 业务错误 - 传入空数据
        auto result = GoodsDetailJsonVO::createShared();
        GoodsDetailDTO::Wrapper emptyData = GoodsDetailDTO::createShared();
        result->fail(emptyData);
        result->code = 404;
        result->message = e.what();
        return result;
    }
    catch (const std::exception& e)
    {
        // 系统错误 - 传入空数据
        auto result = GoodsDetailJsonVO::createShared();
        GoodsDetailDTO::Wrapper emptyData = GoodsDetailDTO::createShared();
        result->fail(emptyData);
        result->code = 500;
        result->message = e.what();
        return result;
    }



}

/*
兑换礼品功能的业务处理
*/
ExchangeResultJsonVO::Wrapper exchangeController::executeSubmitExchange(const ExchangeSubmitDTO::Wrapper& request, const PayloadDTO& payload)
{


    try
    {
        ExchangeService service;


        Int64 userid = std::stoi(payload.getId());
        auto data = service.submitExchange(request, userid);

        auto result = ExchangeResultJsonVO::createShared();
        result->success(data);
        return result;
    }
    catch (const std::invalid_argument& e)
    {
        // 参数错误
        auto result = ExchangeResultJsonVO::createShared();
        ExchangeResultDTO::Wrapper emptyData = ExchangeResultDTO::createShared();
        result->fail(emptyData);
        result->code = 400;
        result->message = e.what();
        return result;
    }
    catch (const std::runtime_error& e)
    {
        // 业务错误
        auto result = ExchangeResultJsonVO::createShared();
        ExchangeResultDTO::Wrapper emptyData = ExchangeResultDTO::createShared();
        result->fail(emptyData);
        result->code = 500;
        result->message = e.what();
        return result;
    }
    catch (const std::exception& e)
    {
        // 系统错误
        auto result = ExchangeResultJsonVO::createShared();
        ExchangeResultDTO::Wrapper emptyData = ExchangeResultDTO::createShared();
        result->fail(emptyData);
        result->code = 500;
        result->message = e.what();
        return result;
    }
}