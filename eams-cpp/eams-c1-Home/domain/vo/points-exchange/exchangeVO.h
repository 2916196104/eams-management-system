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
#ifndef _EXCHANGEVO_H_
#define _EXCHANGEVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/points-exchange/exchangeDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义显示对象
 */

class GoodsPageJsonVO : public JsonVO<GoodsPageDTO::Wrapper>
{
	DTO_INIT(GoodsPageJsonVO, JsonVO<GoodsPageDTO::Wrapper>);
};


class AcceptGoodsPageJsonVO : public JsonVO<AcceptGoodsPageDTO::Wrapper>
{
	DTO_INIT(AcceptGoodsPageJsonVO, JsonVO<AcceptGoodsPageDTO::Wrapper>);
};


class SettingJsonVO : public JsonVO<SettingDTO::Wrapper>
{
	DTO_INIT(SettingJsonVO, JsonVO<SettingDTO::Wrapper>);
};

/**
 * 积分礼品详情响应VO
 */
class GoodsDetailJsonVO : public JsonVO<GoodsDetailDTO::Wrapper>
{
	DTO_INIT(GoodsDetailJsonVO, JsonVO<GoodsDetailDTO::Wrapper>);
};

/**
 * 兑换结果响应VO
 */
class ExchangeResultJsonVO : public JsonVO<ExchangeResultDTO::Wrapper>
{
	DTO_INIT(ExchangeResultJsonVO, JsonVO<ExchangeResultDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_EXCHANGEVO_H_