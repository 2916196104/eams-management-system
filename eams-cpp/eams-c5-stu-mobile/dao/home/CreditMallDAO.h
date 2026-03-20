#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/3/19 10:20:00

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
#ifndef _CREDIT_MALL_DAO_
#define _CREDIT_MALL_DAO_

// 引入基础依赖
#include "BaseDAO.h"
#include "../../domain/do/home/CreditMallDO.h" // 积分商城DO对象（需自行创建）
#include "../../domain/query/home/CreditMallQuery.h"

/**
 * 积分商城礼品DAO层实现
 * 封装credit_mall表的数据库查询/统计操作
 */
class CreditMallDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    CreditMallDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句（WHERE部分）
	// Parameter:   const CreditMallQuery::Wrapper& query 分页查询条件对象
	// Parameter:   SqlParams& params 存放查询参数的对象（防SQL注入）
	// Description: 动态构建积分商城礼品查询条件（支持学校ID/物料ID/分类ID/分类名称等筛选）
	//************************************
	inline std::string queryConditionBuilder(const CreditMallQuery::Wrapper& query, SqlParams& params);

public:
	// 统计符合条件的积分商城礼品总条数
	uint64_t count(const CreditMallQuery::Wrapper& query);

	// 分页查询积分商城礼品数据（支持多条件筛选）
	std::list<CreditMallDO> selectWithPage(const CreditMallQuery::Wrapper& query);

	// 通过礼品名称模糊查询数据
	std::list<CreditMallDO> selectByName(const std::string& name);

	// 通过礼品ID精准查询单条数据
	PtrCreditMallDO selectById(std::string id);
	// 新增单条积分商城礼品数据
	int insert(const CreditMallDO& data);

	// 批量新增积分商城礼品数据
	int insertBatch(const std::list<CreditMallDO>& datas);

	// 修改积分商城礼品数据
	int update(const CreditMallDO& data);

	// 批量更新礼品的删除标记（逻辑删除）
	int updateDeletedByIds(const std::list<std::string>& ids, int deleted = 1);
};

#endif // !_CREDIT_MALL_DAO_