/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/3/19 10:40:00

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
#include "CreditMallDAO.h"
#include "CreditMallMapper .h"
#include <sstream>


// 私有方法：动态构建查询条件（WHERE部分）
std::string CreditMallDAO::queryConditionBuilder(const CreditMallQuery::Wrapper& query, SqlParams& params)
{
	std::stringstream sqlCondition;
	// 基础条件：只查询未删除的礼品（逻辑删除过滤）
	sqlCondition << " WHERE deleted = 0 ";

	// 筛选条件1：学校ID
	if (query->school_id) {
		sqlCondition << " AND school_id = ? ";
		SQLPARAMS_PUSH(params, "ll", uint64_t, query->school_id.getValue(0));
	}

	// 筛选条件2：物料ID
	if (query->material_id) {
		sqlCondition << " AND material_id = ? ";
		SQLPARAMS_PUSH(params, "ll", uint64_t, query->material_id.getValue(0));
	}

	// 筛选条件3：分类ID
	if (query->category_id) {
		sqlCondition << " AND category_id = ? ";
		SQLPARAMS_PUSH(params, "ll", uint64_t, query->category_id.getValue(0));
	}

	// 筛选条件4：分类名称（模糊查询）
	if (!query->category_name->empty()) {
		sqlCondition << " AND category_name LIKE CONCAT('%', ?, '%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->category_name.getValue(""));
	}

	// 筛选条件5：礼品名称（模糊查询）
	if (!query->name->empty()) {
		sqlCondition << " AND name LIKE CONCAT('%', ?, '%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}

	// 筛选条件6：礼品状态（1=可兑换，0=不可兑换）
	if (query->state) {
		sqlCondition << " AND state = ? ";
		SQLPARAMS_PUSH(params, "i", int, query->state.getValue(0));
	}

	return sqlCondition.str();
}

// 统计符合条件的礼品总条数
uint64_t CreditMallDAO::count(const CreditMallQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT COUNT(*) FROM credit_mall ";
	// 构建查询条件（自动过滤已删除数据）
	sql += queryConditionBuilder(query, params);
	// 执行计数查询
	return sqlSession->executeQueryNumerical(sql, params);
}

// 分页查询礼品数据（支持多条件筛选）
std::list<CreditMallDO> CreditMallDAO::selectWithPage(const CreditMallQuery::Wrapper& query)
{
	SqlParams params;
	// 查询字段需与CreditMallMapper中的索引完全一致
	std::string sql = "SELECT "
		"id, school_id, material_id, category_id, category_name, "
		"name, credit, state, sale_num, view_num, "
		"cover, content, creator, editor, add_time, "
		"edit_time, deleted, org_id "
		"FROM credit_mall ";

	// 构建查询条件
	sql += queryConditionBuilder(query, params);

	// 构建排序语句（优先按修改时间降序，无则按创建时间，最后按ID降序）
	sql += " ORDER BY IFNULL(edit_time, add_time) DESC, id DESC ";

	// 构建分页条件（pageIndex从1开始）
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize))
		+ "," + std::to_string(query->pageSize);

	// 执行分页查询，通过映射器转换为DO列表
	return sqlSession->executeQuery<CreditMallDO>(sql, CreditMallMapper(), params);
}

// 通过礼品名称模糊查询数据
std::list<CreditMallDO> CreditMallDAO::selectByName(const std::string& name)
{
	// 查询字段与selectWithPage保持一致
	std::string sql = "SELECT "
		"id, school_id, material_id, category_id, category_name, "
		"name, credit, state, sale_num, view_num, "
		"cover, content, creator, editor, add_time, "
		"edit_time, deleted, org_id "
		"FROM credit_mall "
		"WHERE deleted = 0 AND name LIKE CONCAT('%', ?, '%') ";

	// 执行模糊查询，返回DO列表
	return sqlSession->executeQuery<CreditMallDO>(sql, CreditMallMapper(), "%s", name);
}

// 通过礼品ID精准查询单条数据
PtrCreditMallDO CreditMallDAO::selectById(std::string id)
{
	// 查询字段与selectWithPage保持一致
	std::string sql = "SELECT "
		"id, school_id, material_id, category_id, category_name, "
		"name, credit, state, sale_num, view_num, "
		"cover, content, creator, editor, add_time, "
		"edit_time, deleted, org_id "
		"FROM credit_mall "
		"WHERE deleted = 0 AND id = ? ";

	// 执行单条查询，通过智能指针映射器转换为PtrCreditMallDO
	return sqlSession->executeQueryOne<PtrCreditMallDO>(sql, PtrCreditMallMapper(), "%s", id);
}



// 新增单条礼品数据
int CreditMallDAO::insert(const CreditMallDO& data)
{
	std::string sql = "INSERT INTO credit_mall ( "
		"id, school_id, material_id, category_id, category_name, "
		"name, credit, state, sale_num, view_num, "
		"cover, content, creator, editor, add_time, "
		"edit_time, deleted, org_id "
		") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

	// 执行新增操作，返回受影响行数
	return sqlSession->executeUpdate(sql,
		"%s", data.getId(),                  // id
		"%llu", data.getSchoolId(),          // school_id
		"%llu", data.getMaterialId(),        // material_id
		"%llu", data.getCategoryId(),        // category_id
		"%s", data.getCategoryName(),        // category_name
		"%s", data.getName(),                // name
		"%d", data.getCredit(),              // credit
		"%d", data.getState(),               // state
		"%d", data.getSaleNum(),             // sale_num
		"%d", data.getViewNum(),             // view_num
		"%s", data.getCover(),               // cover
		"%s", data.getContent(),             // content
		"%s", data.getCreator(),             // creator
		"%s", data.getEditor(),              // editor
		"%s", data.getAddTime(),             // add_time
		"%s", data.getEditTime(),            // edit_time
		"%d", data.getDeleted(),             // deleted
		"%llu", data.getOrgId()              // org_id
	);
}

// 批量新增礼品数据
// 批量新增礼品数据（修正版）
int CreditMallDAO::insertBatch(const std::list<CreditMallDO>& datas)
{
	if (datas.empty()) return 0;

	// 累计批量插入的总受影响行数
	int totalAffected = 0;

	// 循环调用已测试通过的insert方法，保证逻辑一致性
	for (const CreditMallDO& data : datas) {
		// 执行单条插入，并累加结果
		int affected = this->insert(data);
		// 可选：插入失败时抛出异常（根据业务需求调整）
		if (affected <= 0) {
			throw std::runtime_error("批量插入失败，礼品ID：" + data.getId());
		}
		totalAffected += affected;
	}

	// 返回批量插入的总行数
	return totalAffected;
}

// 修改礼品数据
int CreditMallDAO::update(const CreditMallDO& data)
{
	std::string sql = "UPDATE credit_mall SET "
		"school_id = ?, material_id = ?, category_id = ?, category_name = ?, "
		"name = ?, credit = ?, state = ?, sale_num = ?, view_num = ?, "
		"cover = ?, content = ?, editor = ?, edit_time = ?, org_id = ? "
		"WHERE id = ? AND deleted = 0 ";

	// 执行修改操作，返回受影响行数
	return sqlSession->executeUpdate(sql,
		"%llu", data.getSchoolId(),          // school_id
		"%llu", data.getMaterialId(),        // material_id
		"%llu", data.getCategoryId(),        // category_id
		"%s", data.getCategoryName(),        // category_name
		"%s", data.getName(),                // name
		"%d", data.getCredit(),              // credit
		"%d", data.getState(),               // state
		"%d", data.getSaleNum(),             // sale_num
		"%d", data.getViewNum(),             // view_num
		"%s", data.getCover(),               // cover
		"%s", data.getContent(),             // content
		"%s", data.getEditor(),              // editor
		"%s", data.getEditTime(),            // edit_time
		"%llu", data.getOrgId(),             // org_id
		"%s", data.getId()                   // 主键ID（WHERE条件）
	);
}

// 批量更新礼品的删除标记（逻辑删除）- 兼容性优先版
int CreditMallDAO::updateDeletedByIds(const std::list<std::string>& ids, int deleted)
{
	if (ids.empty()) return 0;

	// 累计批量更新的总受影响行数
	int totalAffected = 0;

	// 构建单条更新的SQL模板（与你现有update方法格式一致）
	std::string sql = "UPDATE credit_mall SET deleted = ? WHERE id = ? AND deleted = 0 ";

	// 循环执行每条ID的删除操作
	for (const std::string& id : ids) {
		// 复用sqlSession->executeUpdate，参数格式与update方法保持一致
		int affected = sqlSession->executeUpdate(sql,
			"%d", deleted,    // deleted标记值
			"%s", id.c_str()  // 礼品ID
		);

		// 可选：失败时抛出异常，便于排查问题
		if (affected < 0) {
			throw std::runtime_error("批量删除失败，礼品ID：" + id);
		}
		totalAffected += affected;
	}

	// 返回批量更新的总行数
	return totalAffected;
}