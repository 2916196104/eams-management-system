#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: pikachu
 @Date: 2026/3/18 21:10:24

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
#ifndef _CREDIT_MALL_VO_  // 修正：命名和类名统一，避免和原SampleVO冲突
#define _CREDIT_MALL_VO_

#include "../../GlobalInclude.h"
// 修正：引入正确的DTO头文件，替换原SampleDTO
#include "../../dto/home/credit_mallDTO.h"  // 路径请根据实际项目结构调整

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 积分商城礼品单条数据响应VO
 * 用于将credit_mallDTO包装为客户端可识别的JSON响应格式
 */
class credit_mallVO : public JsonVO<credit_mallDTO::Wrapper> {
	DTO_INIT(credit_mallVO, JsonVO<credit_mallDTO::Wrapper>);
};

/**
 * 积分商城礼品分页数据响应VO
 * 用于将分页后的credit_mall数据包装为客户端可识别的JSON响应格式
 */
class credit_mallPageVO : public JsonVO<credit_mallPageDTO::Wrapper> {  // 修正：类名简化且统一
	DTO_INIT(credit_mallPageVO, JsonVO<credit_mallPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_CREDIT_MALL_VO_