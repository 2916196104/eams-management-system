#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/3/19 10:00:00

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
#ifndef _CREDIT_MALL_SERVICE_
#define _CREDIT_MALL_SERVICE_

// 引入核心依赖（路径根据项目实际结构调整）
#include "domain/vo/home/credit_mallVO.h"
#include "domain/query/home/CreditMallQuery.h"
#include "domain/dto/home/credit_mallDTO.h"

/**
 * 积分商城礼品服务实现
 * 封装积分商城礼品的CRUD、批量操作等核心业务逻辑
 */
class CreditMallService
{
public:
    // 分页查询积分商城礼品数据（支持多条件筛选：学校ID/物料ID/分类ID/分类名称等）
    credit_mallPageDTO::Wrapper listAll(const CreditMallQuery::Wrapper& query);

    // 通过ID查询单个积分商城礼品数据
    credit_mallDTO::Wrapper getById(std::string id);

    // 新增单条积分商城礼品数据
    std::string saveData(const credit_mallAddDTO::Wrapper& dto);

    // 批量新增积分商城礼品数据
    bool saveDataBatch(const oatpp::List<credit_mallAddDTO::Wrapper>& datas);

    // 修改积分商城礼品数据
    bool updateData(const credit_mallDTO::Wrapper& dto);

    // 通过ID批量删除积分商城礼品数据（逻辑删除/物理删除）
    bool removeData(const oatpp::List<oatpp::String>& ids);
};

#endif // !_CREDIT_MALL_SERVICE_